/*
 * notes.h
 *
 *  Created on: 25 Oct 2017
 *      Author: Kain
 */

#ifndef SOURCES_NOTES_H_
#define SOURCES_NOTES_H_
#include <stdint.h>


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
	c = 1047,
	cs = 1109,
	d = 1175,
	ds = 1245,
	e = 1319,
	f = 1397,
	fs = 1480,
	g = 1568,
	gs = 1661,
	a = 1760,
	as = 1865,
	b = 1976,
	stop
};

struct noteInfo {
	e_octave octave;
	e_note note;
	int8_t duration;
};

struct noteInfo saints[37];

/*
 * Sets up the FTM module for our note playing
 */
void initNotes();


/*
 *  Takes an integer and adjusts the timer's frequency.
 *
 *   @param freq      takes the desired note frequency
 */
void setNoteFreq(uint16_t freq);


#endif /* SOURCES_NOTES_H_ */
