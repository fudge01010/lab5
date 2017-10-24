/*
 * rtc-code.h
 *
 *  Created on: 25 Oct 2017
 *      Author: Fudge
 */

#ifndef PROJECT_HEADERS_RTC_CODE_H_
#define PROJECT_HEADERS_RTC_CODE_H_
#include <ctime>

void configRTC();
time_t systimeFormat(int seconds);
void handler();
void timeTest(struct timeData *currentTime);

#endif /* PROJECT_HEADERS_RTC_CODE_H_ */
