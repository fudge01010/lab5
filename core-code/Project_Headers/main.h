/*
 * main.h
 *
 *  Created on: 18 Oct 2017
 *      Author: Fudge
 */

#ifndef SOURCES_MAIN_H_
#define SOURCES_MAIN_H_

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
struct time {
	int8_t hr;
	int8_t min;
	int8_t sec;
};



#endif /* SOURCES_MAIN_H_ */