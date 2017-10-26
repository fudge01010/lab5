/*
 * main.h
 *
 *  Created on: 18 Oct 2017
 *      Author: Fudge
 */

#ifndef SOURCES_MAIN_H_
#define SOURCES_MAIN_H_

#ifndef PROJECT_HEADERS_SWITCH_INTERRUPT_H_
#include "switch-interrupt.h"

#endif

/*
 * @name time struct
 * @brief struct that keeps 3 ints containing an h/m/s.
 */
struct timeData {
	int8_t hr;
	int8_t min;
	int8_t sec;
};

/*
 * @name SwitchValue enum
 * @brief enum that contains the switch values
 */
enum SwitchValue {
   noSwitch,    //!< No Switch or multiple switches pressed
   northSwitch, //!< North Switch
   eastSwitch,  //!< East Switch
   southSwitch, //!< South Switch
   westSwitch,  //!< West Switch
   centreSwitch,//!< Centre Switch
};

/*
 * @name timeSetData stuct
 * @brief struct that the timeSetData
 */
struct timeSetData {
	int8_t cursor;
	struct timeData time2set;
};

/*
 * @name alarmSetData stuct
 * @brief struct that the alarmSetData
 */
struct alarmSetData {
	int8_t cursor;
	struct timeData time2set;
};

/*
 * @name settingsScrData stuct
 * @brief struct that the settingsScrData
 */
struct settingsScrData {
	int8_t cursor;
};

/*
 * @name buttonState
 * @brief defing a struct that keeps the buttonState
 */
typedef struct buttonState {
	bool triggered;
	enum SwitchValue direction;
} _buttonState;

/*
 * @name buttonState struct
 * @brief struct that keeps the buttonState
 */
struct buttonState;

/*
 * @name song enum
 * @brief enum that contains the possible songs
 */
enum song {
	marchingIn = 0,
	sandstorm
};

/*
 * @name globalOpt
 * @brief struct that has the song enum //////////////////////////////////////????????????????????????????????????????????????????
 */
struct globalOpt {
	enum song song;
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



int main();
void drawScreen(enum screens currentScreen);
void setupDataObjects();
void actionOnSwitch();


#endif /* SOURCES_MAIN_H_ */
