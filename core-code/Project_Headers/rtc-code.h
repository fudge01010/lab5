/*
 * rtc-code.h
 *
 *  Created on: 25 Oct 2017
 *      Author: Fudge
 */

#ifndef PROJECT_HEADERS_RTC_CODE_H_
#define PROJECT_HEADERS_RTC_CODE_H_
#include <ctime>
#include "main.h"
#include <time.h>


//time_t systimeFormat(int seconds);
//void timeTest(struct timeData *currentTime);


void configRTC();
void getTime(struct timeData *currentTime);

void setRTCTime(timeData time2set);
void setRTCAlarm(timeData time2set);


bool rtcSecInt();
bool rtcAlarmInt();
void secCallback();
void alarmCallback();

#endif /* PROJECT_HEADERS_RTC_CODE_H_ */
