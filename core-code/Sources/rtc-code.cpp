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

using Led = USBDM::GpioA<2,USBDM::ActiveLow>;

void configRTC()
{
	//
//	USBDM::Rtc::setAlarmCallback(handler);
//    USBDM::Rtc::setAlarm(USBDM::Rtc::getTime()+5);
//    USBDM::Rtc::enableAlarmInterrupts();
    USBDM::Rtc::enableNvicInterrupts();
}

void handler(uint32_t timeSinceEpoch) {
   // Set repeat callback for 5 seconds from now
   USBDM::Rtc::setAlarm(timeSinceEpoch+4);
   Led::toggle();
}


time_t systimeFormat(int seconds) {

	time_t t;
	int totalHrs, totalHrsSeconds, totalMinSeconds;

	totalHrs = seconds/3600;
	totalHrsSeconds = totalHrs*3600;

//	t.hrs = totalHrs%12;
//
//	t.mins = (seconds-totalHrsSeconds)/60;
//	totalMinSeconds = t.mins*60;
//
//	t.secs = seconds-totalHrsSeconds-totalMinSeconds;
//
//	if(totalHrs%24 < 12) t.mid = "AM";
//	else t.mid = "PM";
	return t;

}

void timeTest(struct timeData *currentTime) {
	time_t rawtime;
  struct tm * timeinfo;
  char buffer[80];

  time (&rawtime);
  timeinfo = localtime(&rawtime);
  currentTime->hr = timeinfo->tm_hour;
  currentTime->min = timeinfo->tm_min;
  currentTime->sec = timeinfo->tm_sec;
  strftime(buffer, sizeof(buffer), "%d-%m-%Y %I:%M:%S\n", timeinfo);
//  printf(buffer);
}





