/*
 * notes.cpp
 *
 *  Created on: 25 Oct 2017
 *      Author: Kain
 */
#include <stdio.h>
#include "system.h"
#include "derivative.h"
#include "hardware.h"
#include <stdint.h>
#include "notes.h"
#include "pit.h"


//////////////////////////////////////////////////////////////////////////////////////////////
using namespace USBDM;

// Half-period for timer in ticks
// This variable is shared with the interrupt routine
static volatile uint16_t halfPeriod;
static volatile uint16_t halfPeriodNote;


// Waveform period to generate
static const float WAVEFORM_PERIOD = 0.5*ms;

using Timer = Ftm1;
using TimerNote = Ftm0;
using TimerChannel = Ftm1Channel<1>;
using TimerChannelNote = Ftm0Channel<1>;
using spkGnd = GpioA<5, ActiveLow>;

static volatile noteInfo saints[37];
static bool playingTrack = false;
static int duration = 0;
static bool nextNote = false;

//callback for tone
static void ftmCallback(uint8_t status) {

   // Check channel
   if (status & TimerChannel::CHANNEL_MASK) {
      // Note: The pin is toggled directly by hardware
      // Re-trigger at last interrupt time + timerHalfPeriodInTicks
      TimerChannel::setDeltaEventTime(halfPeriod);
   }
}

//callback for our note
void ftmCallbackNote() {
	printf("callback\n");
	nextNote = true;
}

//Setup interrupts
void setupSpeakerInterrupts() {
	noteIndex = 0;
	spkGnd::setOutput(PinDriveStrength_High, PinDriveMode_OpenDrain, PinSlewRate_Fast);

	Timer::configure(
		FtmMode_LeftAlign,      // Left-aligned is required for OC/IC
		FtmClockSource_System,  // Bus clock usually
		FtmPrescale_1);         // The prescaler will be re-calculated later

	// Set IC/OC measurement period to accommodate maximum period + 10%
	// This adjusts the prescaler value but does not change the clock source
	Timer::setMeasurementPeriod(1.1*WAVEFORM_PERIOD/2.0);
	printf("test1\n");
	// Calculate half-period in timer ticks
	// Must be done after timer clock configuration (above)
	halfPeriod = Timer::convertSecondsToTicks(WAVEFORM_PERIOD/2.0);
	printf("%i\n", halfPeriod);

	// Set callback function
	Timer::setChannelCallback(ftmCallback);

	// Enable interrupts for entire timer
	Timer::enableNvicInterrupts();

	// Configure pin associated with channel
	TimerChannel::setDriveStrength(PinDriveStrength_High);

	// Trigger 1st interrupt at now+100
	TimerChannel::setRelativeEventTime(100);
	printf("test2\n");
	// Configure the channel
	TimerChannel::configure(
		FtmChMode_OutputCompareToggle, //  Output Compare with pin toggle
		FtmChannelIrq_Enable);         //  + interrupts on events


	Pit::configure();

	Pit::setCallback(2, ftmCallbackNote);

	Pit::configureChannelInTicks(2, ::SystemBusClock/4);

	// Enable interrupts on the channel
	Pit::enableInterrupts(2);

	// Check for errors so far
	checkError();
}

//Music handler controls the playing of the song
void musicHandler() {
	if (!playingTrack) {
		setNoteFreq(1000);
	} else if (nextNote) {
		if (playingTrack)
		{
			if (duration == 0)
			{
				//no duration left or we've just started. get next note:
				setNoteFreq((uint16_t)saints[noteIndex].note);
				printf("%i\n", (uint16_t)noteIndex);
				printf("set freq as %d\n", saints[noteIndex].note);
				duration = saints[noteIndex].duration-1;
				noteIndex++;
			} else if (duration > 0) {
				duration--;
			}
		}
		nextNote = false;
	}
}

//Stop alarm
void stopAlarm () {
	playingTrack = false;
}

//Sets the note frequency for our song
void setNoteFreq(uint16_t noteFreq) {
	halfPeriod = noteFreq;
}

//Start alarm
void startAlarm () {
	playingTrack = true;
}

//Loads the notes/octave and durations for each note of the song.
void loadSongSaints () {
	//First line 4
//	saints = noteInfo saints[37];
	saints[0].octave = o6;
	saints[0].note = c;
	saints[0].duration = 1;

	saints[1].octave = o6;
	saints[1].note = e;
	saints[1].duration = 1;

	saints[2].octave = o6;
	saints[2].note = f;
	saints[2].duration = 1;

	saints[3].octave = o6;
	saints[3].note = g;
	saints[3].duration = 4;

	//Second line 5
	saints[4].octave = o6;
	saints[4].note = g;
	saints[4].duration = 1;

	saints[5].octave = o6;
	saints[5].note = c;
	saints[5].duration = 1;

	saints[6].octave = o6;
	saints[6].note = e;
	saints[6].duration = 1;

	saints[7].octave = o6;
	saints[7].note = f;
	saints[7].duration = 1;

	saints[8].octave = o6;
	saints[8].note = g;
	saints[8].duration = 4;

	//Third line 6
	saints[9].octave = o6;
	saints[9].note = g;
	saints[9].duration = 1;

	saints[10].octave = o6;
	saints[10].note = c;
	saints[10].duration = 1;

	saints[11].octave = o6;
	saints[11].note = e;
	saints[11].duration = 1;

	saints[12].octave = o6;
	saints[12].note = f;
	saints[12].duration = 1;

	saints[13].octave = o6;
	saints[13].note = g;
	saints[13].duration = 2;

	saints[14].octave = o6;
	saints[14].note = e;
	saints[14].duration = 2;

	//Fourth line 3
	saints[15].octave = o6;
	saints[15].note = c;
	saints[15].duration = 2;

	saints[16].octave = o6;
	saints[16].note = e;
	saints[16].duration = 2;

	saints[17].octave = o6;
	saints[17].note = cs;
	saints[17].duration = 4;

	//Fifth line 6
	saints[18].octave = o6;
	saints[18].note = d;
	saints[18].duration = 1;

	saints[19].octave = o6;
	saints[19].note = e;
	saints[19].duration = 1;

	saints[20].octave = o6;
	saints[20].note = e;
	saints[20].duration = 1;

	saints[21].octave = o6;
	saints[21].note = d;
	saints[21].duration = 1;

	saints[22].octave = o6;
	saints[22].note = c;
	saints[22].duration = 3;

	saints[23].octave = o6;
	saints[23].note = c;
	saints[23].duration = 1;

	//Sixth line 4
	saints[24].octave = o6;
	saints[24].note = e;
	saints[24].duration = 2;

	saints[25].octave = o6;
	saints[25].note = g;
	saints[25].duration = 2;

	saints[26].octave = o6;
	saints[26].note = g;
	saints[26].duration = 1;

	saints[27].octave = o6;
	saints[27].note = f;
	saints[27].duration = 3;

	//Seventh line 5
	saints[28].octave = o6;
	saints[28].note = f;
	saints[28].duration = 2;

	saints[29].octave = o6;
	saints[29].note = e;
	saints[29].duration = 1;

	saints[30].octave = o6;
	saints[30].note = f;
	saints[30].duration = 1;

	saints[31].octave = o6;
	saints[31].note = g;
	saints[31].duration = 2;

	saints[32].octave = o6;
	saints[32].note = e;
	saints[32].duration = 2;

	//Eighth line 3
	saints[33].octave = o6;
	saints[33].note = c;
	saints[33].duration = 2;

	saints[34].octave = o6;
	saints[34].note = d;
	saints[34].duration = 2;

	saints[35].octave = o6;
	saints[35].note = c;
	saints[35].duration = 4;

	//Ninth line 1
	saints[36].octave = o6;
	saints[36].note = c;
	saints[36].duration = 1;

	//STOP
	saints[37].octave = o6;
	saints[37].note = stop;
	saints[37].duration = 0;
}
