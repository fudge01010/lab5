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



//static struct buttonState swState;
//struct buttonState buttonState;

struct buttonState;

/*
 * This callback is set programmatically
 *
 * It polls the switch and provides a debounced result in switchValue
 */
void deBouncer();


/**
 * Configures all 5-way button interrupts, pins, handlers, etc.
 *
 * @param address of swState variable - not used.
 *
 * @return nil
 */
void configure5wayInterrupt(struct buttonState *buttonData);

/**
 * Returns the state of the debounced buttons
 *
 * @param nil
 *
 * @return buttonState struct - containing button status + button direction enum.
 */
struct buttonState pullFromMem();

#endif /* PROJECT_HEADERS_SWITCH_INTERRUPT_H_ */
