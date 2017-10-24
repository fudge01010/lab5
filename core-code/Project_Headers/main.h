/*
 * main.h
 *
 *  Created on: 18 Oct 2017
 *      Author: Fudge
 */

#ifndef SOURCES_MAIN_H_
#define SOURCES_MAIN_H_

/*
 * @name time struct
 * @brief struct that keeps 3 ints containing an h/m/s.
 */
struct timeData {
	int8_t hr;
	int8_t min;
	int8_t sec;
};

struct timeSetData {
	int8_t cursor;
};

struct alarmSetData {
	int8_t cursor;
};

struct settingsScrData {
	int8_t cursor;
};

typedef struct buttonState {
	bool triggered;
	int8_t direction;
} _buttonState;

struct buttonState;

//static buttonState buttonState;

enum song {
	marchingIn = 0,
	sandstorm
};

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


#endif /* SOURCES_MAIN_H_ */
