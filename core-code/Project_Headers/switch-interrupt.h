/*
 * switch-interrupt.h
 *
 *  Created on: 24 Oct 2017
 *      Author: Fudge
 */

#ifndef PROJECT_HEADERS_SWITCH_INTERRUPT_H_
#define PROJECT_HEADERS_SWITCH_INTERRUPT_H_


/**
 * Enum representing the different possible switch values
 */
enum SwitchValue {
   noSwitch,    //!< No Switch or multiple switches pressed
   eastSwitch,  //!< East Switch
   southSwitch, //!< South Switch
   westSwitch,  //!< West Switch
   centreSwitch,//!< Centre Switch
   northSwitch, //!< North Switch
};


//static struct buttonState swState;
//struct buttonState buttonState;

struct buttonState;



void configure5wayInterrupt(struct buttonState *buttonData);
void switchTest();

#endif /* PROJECT_HEADERS_SWITCH_INTERRUPT_H_ */
