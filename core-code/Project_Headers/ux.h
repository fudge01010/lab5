/*
 * ux.h
 *
 *  Created on: 24 Oct 2017
 *      Author: Kain
 */

#ifndef SOURCES_UX_H_
#define SOURCES_UX_H_

/*
 * @name drawTimeScreen
 * @brief The screen for the time
 * @params currentTime gets the current time
 */
void drawTimeScreen(struct timeData currentTime);

/*
 * @name drawTimeSetScreen
 * @brief The screen for setting the time
 * @params currentTime gets the current time
 */
void drawTimeSetScreen(struct timeSetData setData);

/*
 * @name drawAlarmSetScreen
 * @brief The screen for setting the alarm
 * @params alarmSettingsData passes the alarm settings including the cursor
 */
void drawAlarmSetScreen(struct alarmSetData alarmSettingsData);

/*
 * @name drawSettingsScreen
 * @brief The screen for the settings menu
 * @params settingnsScrData passes the screen data incuding the cursor
 * @params globalOpt contains the song
 */
void drawSettingsScreen(struct settingsScrData, struct globalOpt);

/*
 * @name drawAlarmScreen
 * @brief The screen for the alarm
 */
void drawAlarmScreen();

/*
 * @name clearScreen
 * @brief Clears the screen
 */
void clearScreen();

#endif /* SOURCES_UX_H_ */
