/*
 * notes.h
 *
 *  Created on: 26 Oct 2017
 *      Author: Kain
 */

#ifndef PROJECT_HEADERS_NOTES_H_
#define PROJECT_HEADERS_NOTES_H_

/*
 * 	@name octave enum
 * 	@brief enum for the different octaves used in the tone generator.
 */
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

/*
 * 	@name note enum
 * 	@brief enum for the different notes/frequencies used in the tone generator.
 */
enum e_note {
	c = 23436, //1047,
	cs = 22692, //1109,
	d = 21900, //1175,
	ds = 21060, //1245,
	e = 20172, //1319,
	f = 19236, //1397,
	fs = 18240, //1480,
	g = 17184, //1568,
	gs = 16068, //1661,
	a = 14880, //1760,
	as = 13620, //1865,
	b = 12288, //1976,
	stop = 1000
};

/*
 * 	@name noteInfo struct
 * 	@brief struct for the noteInfo, contains the provided saints songs.
 */
typedef struct s_noteInfo {
	e_octave octave;
	e_note note;
	int8_t duration;
}noteInfo;

/*
 * 	@name noteIndex int
 * 	@brief int to keep track of the note playing.
 */
static int noteIndex;

/*
 * @name noteIndex int
 * @breif Sets up the FTM module for our note playing.
 */
void setupSpeakerInterrupts();

/*
 * @name startAlarm
 * @breif Sets playingTrack to true, which allows the tone to play.
 */
void startAlarm ();

/*
 * @name stopAlarm
 * @breif Sets playingTrack to false, which stops the tone from playing.
 */
void stopAlarm ();

/*
 * @name loadSongSaints
 * @breif Loads the saints tone struct for playing.
 */
void loadSongSaints ();


void musicHandler();

/*
 * @name setNoteFreq
 * @breif Takes an integer and adjusts the timer's frequency.
 * @param freq      takes the desired note frequency
 */
void setNoteFreq(uint16_t freq);

#endif /* PROJECT_HEADERS_NOTES_H_ */
