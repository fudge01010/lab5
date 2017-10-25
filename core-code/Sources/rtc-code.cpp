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



void secCallback(uint32_t timeSinceEpoch) {
	rtcSecTrig = true;
}

void alarmCallback(uint32_t timeSinceEpoch) {
	rtcAlarmTrig = true;
}


//time_t systimeFormat(int seconds) {
//
//	time_t t;
//	int totalHrs, totalHrsSeconds, totalMinSeconds;
//
//	totalHrs = seconds/3600;
//	totalHrsSeconds = totalHrs*3600;
//
////	t.hrs = totalHrs%12;
////
////	t.mins = (seconds-totalHrsSeconds)/60;
////	totalMinSeconds = t.mins*60;
////
////	t.secs = seconds-totalHrsSeconds-totalMinSeconds;
////
////	if(totalHrs%24 < 12) t.mid = "AM";
////	else t.mid = "PM";
//	return t;
//
//}

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

void setRTCTime(timeData time2set){
	//
	uint32_t epochSeconds = 0;
	epochSeconds += time2set.hr * 3600;
	epochSeconds += time2set.min * 60;
	epochSeconds += time2set.sec;
	USBDM::Rtc::setTime(epochSeconds);

}

void setRTCAlarm(timeData time2set){
	//
	uint32_t epochSeconds = 0;
	epochSeconds += time2set.hr * 3600;
	epochSeconds += time2set.min * 60;
	epochSeconds += time2set.sec;
	USBDM::Rtc::setAlarm(epochSeconds);

}

void configRTC() {
//	USBDM::Rtc::setSecondsCallback(secCallback);
//	USBDM::Rtc::setAlarmCallback(alarmCallback);
//    USBDM::Rtc::enableNvicInterrupts();
}


//the poll-able funcs to see if callbacks are hit.

bool rtcSecInt() {
	if (rtcSecTrig) {
		rtcSecTrig = false;
		return true;
	} else
		return false;
}

bool rtcAlarmInt() {
	if (rtcAlarmTrig) {
		rtcAlarmTrig = false;
		return true;
	} else
		return false;
}

//void timeTest(struct timeData *currentTime) {
//	time_t rawtime;
//  struct tm * timeinfo;
////  char buffer[80];
//
//  time (&rawtime);
//  timeinfo = localtime(&rawtime);
//  currentTime->hr = timeinfo->tm_hour;
//  currentTime->min = timeinfo->tm_min;
//  currentTime->sec = timeinfo->tm_sec;
////  strftime(buffer, sizeof(buffer), "%I:%M:%S\n", timeinfo);
////  printf(buffer);
//}





