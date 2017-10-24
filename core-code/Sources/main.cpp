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


int main() {

	timeSetScreenData.cursor = 0;

	currentTime.hr = 0;
	currentTime.min = 0;
	currentTime.sec = 0;
	printf("test\n");
	buttonData.triggered = false;
	configure5wayInterrupt(&buttonData);
	if (buttonData.triggered == true)
	{
		printf("holy fuck I am good");
	}
	printf("config'd\n");

   for(;;) {
//	   	  //during debugging, this is our "heartbeat" LED"
	      Led::toggle();
////		  asm("wfi");
		  waitMS(250);
		  drawScreen((screens)2);
//		  currentTime.sec += 1;
//	   printf("l\n");
	   switchTest();
	   timeTest(&currentTime);


   }
   //never reach
   return 0;
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
