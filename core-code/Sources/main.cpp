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
#include "rtc-code.h"
#include "switch-interrupt.h"


// Allow access to USBDM methods without USBDM:: prefix
using namespace USBDM;

using Led   = USBDM::GpioA<2,USBDM::ActiveLow>;


// static struct for the current time;
struct timeData currentTime;
//struct containing the time of the alarm
static struct timeData alarmTime;
static struct timeSetData timeSetScreenData;
static struct alarmSetData alarmSetScreenData;
static struct settingsScrData settingsScreenData;
static struct globalOpt globalSettings;

static buttonState buttonData;

static enum screens currentScreen;

static bool switchActioned = false;


int main() {
	setupDataObjects();
	timeSetScreenData.cursor = 0;
//	currentTime.hr = 0;
//	currentTime.min = 0;
//	currentTime.sec = 0;
	printf("test\n");
	buttonData.triggered = false;
	configure5wayInterrupt(&buttonData);
	if (buttonData.triggered == true)
	{
		printf("holy fuck I am good");
	}
	printf("config'd\n");

   for(;;) {
	   //mainline loop
//	   	  //during debugging, this is our "heartbeat" LED"
	   if (buttonData.triggered && !switchActioned) {
		   //if a button has been pressed and we haven't done anything about it, process it
		   switchActioned = true;
		   actionOnSwitch();
	   } else if (!buttonData.triggered && switchActioned) {
		   //if we've released the button yet action flag is still set, clear it.
		   switchActioned = false;
	   }
	      Led::toggle();
////		  asm("wfi");
		  waitMS(250);
		  drawScreen((screens)2);
//		  currentTime.sec += 1;
//	   printf("l\n");
//	   switchTest();
	   timeTest(&currentTime);


   }
   //never reach
   return 0;
}

void actionOnSwitch() {
	//switch what happens depending on what screen we're on
	switch (currentScreen) {
	case timeScreen:
		//we only care about centre clicks on the time screen
		if (buttonData.direction == 1) {
			currentScreen = settingsScreen;
		}
		break;
	case alarmScreen:
		//if we're alarming, any button press should go back to the time
		if (buttonData.direction != 0) {
			currentScreen = timeScreen;
		}
		break;
	case timeSetScreen:
		//if we're setting the time, move the cursor or inc time.
		if (timeSetScreenData.cursor < 2 && buttonData.direction == 3)
		{
			timeSetScreenData.cursor++;
		} else if (timeSetScreenData.cursor > 0 && buttonData.direction == 0) {
			//
		}
		break;
	case alarmSetScreen:
		//
		break;
	case settingsScreen:
		//
		break;
	default:
		break;
	}
}

void setupDataObjects() {
	//set up switch data
	buttonData.triggered = false;
	buttonData.direction = noSwitch;
}

void drawScreen(enum screens currentScreen) {
//	enum screens &currentScreen
	switch (currentScreen) {
	//
	case timeScreen :
		drawTimeScreen(currentTime);
		break;
	case alarmScreen :
//		drawAlarmScreen(&currentTime);
		break;
	case timeSetScreen :
		drawTimeSetScreen(&currentTime, timeSetScreenData);
		break;
	case alarmSetScreen :
//		drawAlarmSetScreen(&alarmTime, &alarmSetScreenData);
		break;
	case settingsScreen :
//		drawSettingsScreen(&settingsScreenData, &globalSettings);
		break;
	default:
		break;
	}

}
