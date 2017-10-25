/*
 * ux.h
 *
 *  Created on: 24 Oct 2017
 *      Author: Kain
 */

#ifndef SOURCES_UX_H_
#define SOURCES_UX_H_

/*
 * @name time struct
 * @brief struct that keeps 3 ints containing an h/m/s.
 */
//struct time {
//	int8_t hr;
//	int8_t min;
//	int8_t sec;
//};

void drawTimeScreen(struct timeData currentTime);
void drawTimeSetScreen(struct timeSetData setData);
void drawAlarmSetScreen(struct alarmSetData alarmSettingsData);
void drawSettingsScreen(struct settingsScrData, struct globalOpt);
void drawAlarmScreen();

void clearScreen();

#endif /* SOURCES_UX_H_ */
