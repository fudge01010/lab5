/*
 * rtc-code.cpp
 *
 *  Created on: 25 Oct 2017
 *      Author: Fudge
 */
#include "rtc.h"
#include "rtc-code.h"
#include <stdio.h>
#include <ctime>
#include "main.h"
#include "system.h"
#include "derivative.h"
#include "hardware.h"
#include <time.h>


static bool rtcSecTrig = false;
static bool rtcAlarmTrig = false;


/**
 * The callback for the RTC seconds. sets a flag.
 *
 * @param timeSinceEpoch - not used, but required by callback handler.
 *
 * @return nil
 */
void secCallback(uint32_t timeSinceEpoch) {
	rtcSecTrig = true;
//	printf("callbacked");
}

/**
 * The callback for the RTC alarm. sets a flag.
 *
 * @param timeSinceEpoch - not used, but required by callback handler.
 *
 * @return nil
 */
void alarmCallback(uint32_t timeSinceEpoch) {
	rtcAlarmTrig = true;
}

/**
 * Reads the time from the RTC, and writes it into the struct for currentTime
 * NB: this struct is passed in via address from the calling function.
 *
 * @param timeData struct - passed in via address from calling function.
 *
 * @return nil
 */
void getTime(struct timeData *currentTime) {
 	time_t rawtime;
 	 struct tm * timeinfo;
	//  char buffer[80];
	time (&rawtime);
	 timeinfo = localtime(&rawtime);
	 currentTime->hr = timeinfo->tm_hour;
	 currentTime->min = timeinfo->tm_min;
 	 currentTime->sec = timeinfo->tm_sec;
}

/**
 * Sets the RTC time in epoch seconds.
 *
 * @param timeData struct for the time to set. Converted to epoch internally.
 *
 * @return nil
 */
void setRTCTime(timeData time2set){
	//
	uint32_t epochSeconds = 0;
	epochSeconds += time2set.hr * 3600;
	epochSeconds += time2set.min * 60;
	epochSeconds += time2set.sec;
	USBDM::Rtc::setTime(epochSeconds);

}

/**
 * Sets the RTC alarm in epoch seconds.
 *
 * @param timeData struct for the time to set. Converted to epoch internally.
 *
 * @return nil
 */
void setRTCAlarm(timeData time2set){
	//
	uint32_t epochSeconds = 0;
	epochSeconds += time2set.hr * 3600;
	epochSeconds += time2set.min * 60;
	epochSeconds += time2set.sec;
	USBDM::Rtc::setAlarm(epochSeconds);
//	printf("%d",epochSeconds);

}

/**
 * Configures the alarm + seconds callbacks, and enables their interrupts.
 *
 * @param nil
 *
 * @return nil
 */
void configRTC() {
//	USBDM::Rtc::setSecondsCallback(secCallback);
	USBDM::Rtc::setAlarmCallback(alarmCallback);
    USBDM::Rtc::enableNvicInterrupts();

}


//the poll-able funcs to see if callbacks are hit.
/**
 * Returns the interrupt flag status (wrapper to de-globalize variable.
 *
 * @param nil
 *
 * @return nil
 */
bool rtcSecInt() {
	if (rtcSecTrig) {
		rtcSecTrig = false;
		return true;
	} else
		return false;
}

/**
 * Returns the interrupt flag status (wrapper to de-globalize variable.
 *
 * @param nil
 *
 * @return nil
 */
bool rtcAlarmInt() {
	if (rtcAlarmTrig) {
		rtcAlarmTrig = false;
		return true;
	} else
		return false;
}





