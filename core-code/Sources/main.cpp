/*
 ============================================================================
 * @file    main.cpp (180.ARM_Peripherals/Sources/main.cpp)
 * @brief   Basic C++ demo using GPIO class
 *
 *  Created on: 10/1/2016
 *      Author: podonoghue
 ============================================================================
 */
#include <stdio.h>
#include "system.h"
#include "main.h"
#include "derivative.h"
#include "hardware.h"
#include "ux.h"


// Allow access to USBDM methods without USBDM:: prefix
using namespace USBDM;


// static struct for the current time;
static struct time currentTime;
//struct containing the time of the alarm
static struct time alarmTime;

static enum screens currentScreen;

int main() {

	currentTime.hr = 0;
	currentTime.min = 0;
	currentTime.sec = 0;
   for(;;) {
	   asm("wfi");
	   waitMS(1000);
	   drawScreen((screens)0);
	   currentTime.hr += 1;
   }
   return 0;
}

void drawScreen(enum screens currentScreen) {
	//enum screens &currentScreen
	switch (currentScreen) {
	//
	case timeScreen :
		drawTimeScreen(&currentTime);
		break;
	default:
		break;
	}

}
