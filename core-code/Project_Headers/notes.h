/*
 * notes.h
 *
 *  Created on: 26 Oct 2017
 *      Author: Kain
 */

#ifndef PROJECT_HEADERS_NOTES_H_
#define PROJECT_HEADERS_NOTES_H_

enum e_octave {
	o1 = 1,
	o2,
	o3,
	o4,
	o5,
	o6,
	o7,
	o8
};

enum e_note {
	c = 1047,
	cs = 1109,
	d = 1175,
	ds = 1245,
	e = 1319,
	f = 1397,
	fs = 1480,
	g = 1568,
	gs = 1661,
	a = 1760,
	as = 1865,
	b = 1976,
	stop
};

typedef struct s_noteInfo {
	e_octave octave;
	e_note note;
	int8_t duration;
}noteInfo;


/*
 * Sets up the FTM module for our note playing
 */
void setupSpeakerInterrupts();


/*
 *  Takes an integer and adjusts the timer's frequency.
 *
 *   @param freq      takes the desired note frequency
 */
void setNoteFreq(uint16_t freq);

#endif /* PROJECT_HEADERS_NOTES_H_ */
