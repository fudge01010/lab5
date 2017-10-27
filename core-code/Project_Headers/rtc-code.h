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


/**
 * Configures the alarm + seconds callbacks, and enables their interrupts.
 *
 * @param nil
 *
 * @return nil
 */
void configRTC();

/**
 * Reads the time from the RTC, and writes it into the struct for currentTime
 * NB: this struct is passed in via address from the calling function.
 *
 * @param timeData struct - passed in via address from calling function.
 *
 * @return nil
 */
void getTime(struct timeData *currentTime);

/**
 * Sets the RTC time in epoch seconds.
 *
 * @param timeData struct for the time to set. Converted to epoch internally.
 *
 * @return nil
 */
void setRTCTime(timeData time2set);

/**
 * Sets the RTC alarm in epoch seconds.
 *
 * @param timeData struct for the time to set. Converted to epoch internally.
 *
 * @return nil
 */
void setRTCAlarm(timeData time2set);

/**
 * Returns the interrupt flag status (wrapper to de-globalize variable.
 *
 * @param nil
 *
 * @return nil
 */
bool rtcSecInt();

/**
 * Returns the interrupt flag status (wrapper to de-globalize variable.
 *
 * @param nil
 *
 * @return nil
 */
bool rtcAlarmInt();

/**
 * The callback for the RTC seconds. sets a flag.
 *
 * @param timeSinceEpoch - not used, but required by callback handler.
 *
 * @return nil
 */
void secCallback();

/**
 * The callback for the RTC alarm. sets a flag.
 *
 * @param timeSinceEpoch - not used, but required by callback handler.
 *
 * @return nil
 */
void alarmCallback();

#endif /* PROJECT_HEADERS_RTC_CODE_H_ */
