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

enum e_octave {
	o1 = 1,
	o2,
	o3,
	o4,
	o5,
	o6,
	o7,
	o8
};

enum e_note {
	c = 2093,
	cs = 2217,
	d = 2349,
	ds = 2489,
	e = 2637,
	f = 2794,
	fs = 2960,
	g = 3136,
	gs = 3320,
	a = 3520,
	as = 3729,
	b = 3951
};

struct noteInfo {
	e_octave octave;
	e_note note;
	uint8_t duration;
};

struct noteInfo saints[24];

#endif /* PROJECT_HEADERS_RTC_CODE_H_ */