/*
 * main.h
 *
 *  Created on: 18 Oct 2017
 *      Author: Fudge
 */

#ifndef SOURCES_MAIN_H_
#define SOURCES_MAIN_H_

struct time {
	int8_t hr;
	int8_t min;
	int8_t sec;
};

/*
 * 	@name screen enum
 * 	@brief enum for the different possible screens to draw.
 */

enum screens {
	timeScreen = 0,
	alarmScreen,
	timeSetScreen,
	alarmSetScreen,
	settingsScreen
};

/*
 * @name time struct
 * @brief struct that keeps 3 ints containing an h/m/s.
 */


int main();
void drawScreen(enum screens currentScreen);


#endif /* SOURCES_MAIN_H_ */
