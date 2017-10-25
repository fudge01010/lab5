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
#include "bmp.h"


// Allow access to USBDM methods without USBDM:: prefix
using namespace USBDM;

// static struct for the current time;
struct timeData currentTime;
////struct containing the time of the alarm
static struct timeSetData timeSetScreenData;
static struct alarmSetData alarmSetScreenData;
static struct settingsScrData settingsScreenData;
static struct globalOpt globalSettings;

static buttonState buttonData;

static enum screens currentScreen;
static enum screens prevScreen;

static bool switchActioned = false;
static bool secIntTriggered = false;
static bool almIntTriggered = false;


int main() {
	setupDataObjects();
	configRTC();
	printf("test\n");
	configure5wayInterrupt(&buttonData);
	printf("config'd\n");

   for(;;) {
	   //mainline loop
	   buttonData = pullFromMem();
	   if (buttonData.triggered && !switchActioned) {
		   //if a button has been pressed and we haven't done anything about it, process it
		   switchActioned = true;
		   printf("actioning\n");
		   actionOnSwitch();
	   } else if (!buttonData.triggered && switchActioned) {
		   //if we've released the button yet action flag is still set, clear it.
		   switchActioned = false;
	   }
	   secIntTriggered = rtcSecInt();
	   almIntTriggered = rtcAlarmInt();

	   waitMS(50);
	   drawScreen(currentScreen);
//	   printf("%d\n", currentScreen);

   }
   //never reach
   return 0;
}

void actionOnSwitch() {
	//switch what happens depending on what screen we're on
	switch (currentScreen) {
	case timeScreen:
		//we only care about centre clicks on the time screen, to go to settings.
		if (buttonData.direction == centreSwitch) {
			currentScreen = settingsScreen;
		}
		break;
	case alarmScreen:
		//if we're alarming, any button press should go back to the time
		if (buttonData.direction != noSwitch) {
			currentScreen = timeScreen;
		}
		break;
	case timeSetScreen:
		//if we're setting the time, move the cursor or inc/dec time.
		if (timeSetScreenData.cursor < 2 && buttonData.direction == eastSwitch)
		{
			timeSetScreenData.cursor++;
		} else if (timeSetScreenData.cursor > 0 && buttonData.direction == westSwitch) {
			timeSetScreenData.cursor--;
		}
		if (buttonData.direction == northSwitch)
		{
			//switch is up. increment time
			if (timeSetScreenData.cursor == 0 && timeSetScreenData.time2set.hr < 23) {
				timeSetScreenData.time2set.hr ++;
			} else if (timeSetScreenData.cursor == 1 && timeSetScreenData.time2set.min < 59) {
				timeSetScreenData.time2set.min++;
			} else if (timeSetScreenData.cursor == 2 && timeSetScreenData.time2set.sec < 59) {
				timeSetScreenData.time2set.sec++;
			}
		} else if (buttonData.direction == southSwitch)
		{
			//switch is down. decrement time.
			if (timeSetScreenData.cursor == 0 && timeSetScreenData.time2set.hr > 0) {
				timeSetScreenData.time2set.hr--;
			} else if (timeSetScreenData.cursor == 1 && timeSetScreenData.time2set.min > 0) {
				timeSetScreenData.time2set.min--;
			} else if (timeSetScreenData.cursor == 2 && timeSetScreenData.time2set.sec > 0) {
				timeSetScreenData.time2set.sec--;
			}
		}
		if (buttonData.direction == centreSwitch) {
			//set the time based on the current programmed time.
			setRTCTime(timeSetScreenData.time2set);
			currentScreen = timeScreen;
		}
		break;
	case alarmSetScreen:
		//if we're setting the time, move the cursor or inc/dec time.
		if (alarmSetScreenData.cursor < 2 && buttonData.direction == eastSwitch)
		{
			alarmSetScreenData.cursor++;
		} else if (alarmSetScreenData.cursor > 0 && buttonData.direction == westSwitch) {
			alarmSetScreenData.cursor--;
		}
		if (buttonData.direction == northSwitch)
		{
			//switch is up. increment time
			if (alarmSetScreenData.cursor == 0 && alarmSetScreenData.time2set.hr < 23) {
				alarmSetScreenData.time2set.hr ++;
			} else if (alarmSetScreenData.cursor == 1 && alarmSetScreenData.time2set.min < 59) {
				alarmSetScreenData.time2set.min++;
			} else if (alarmSetScreenData.cursor == 2 && alarmSetScreenData.time2set.sec < 59) {
				alarmSetScreenData.time2set.sec++;
			}
		} else if (buttonData.direction == southSwitch)
		{
			//switch is down. decrement time.
			if (alarmSetScreenData.cursor == 0 && alarmSetScreenData.time2set.hr > 0) {
				alarmSetScreenData.time2set.hr--;
			} else if (alarmSetScreenData.cursor == 1 && alarmSetScreenData.time2set.min > 0) {
				alarmSetScreenData.time2set.min--;
			} else if (alarmSetScreenData.cursor == 2 && alarmSetScreenData.time2set.sec > 0) {
				alarmSetScreenData.time2set.sec--;
			}
		}
		if (buttonData.direction == centreSwitch) {
			//set the alarm time based on the current programmed time.
			//setAlarm(alarmSetScreenData.time2set);
			currentScreen = settingsScreen;
		}
		break;
	case settingsScreen:
		if (buttonData.direction == southSwitch && settingsScreenData.cursor < 3)
			settingsScreenData.cursor++;
		if (buttonData.direction == northSwitch && settingsScreenData.cursor > 0)
			settingsScreenData.cursor--;
		if (buttonData.direction == centreSwitch)
		{
			//switch based on cursor position
			switch (settingsScreenData.cursor){
			case 0:
				currentScreen = timeSetScreen;
				timeSetScreenData.time2set = currentTime;
				break;
			case 1:
				currentScreen = alarmSetScreen;
				break;
			case 2:
				//current screen = alarm tone set screen;
				currentScreen = alarmScreen;
				break;
			case 3:
				currentScreen = timeScreen;
				break;
			default:
				break;
			}


		}
		break;
	default:
		break;
	}
}

void setupDataObjects() {
	//set up switch data
	buttonData.triggered = false;
	buttonData.direction = noSwitch;

//	timeSetScreenData.cursor = 2;

	//start at clock screen

	prevScreen = currentScreen = timeScreen;
}

void drawScreen(enum screens currentScreen) {
//	enum screens &currentScreen;
	if (prevScreen != currentScreen) {
		clearScreen();
		prevScreen = currentScreen;
	}
	switch (currentScreen) {
	//
	case timeScreen :
		drawTimeScreen(currentTime);
		break;
	case alarmScreen :
		drawAlarmScreen();
		break;
	case timeSetScreen :
		drawTimeSetScreen(timeSetScreenData);
		break;
	case alarmSetScreen :
		drawAlarmSetScreen(alarmSetScreenData);
		break;
	case settingsScreen :
		drawSettingsScreen(settingsScreenData, globalSettings);
		break;
	default:
		break;
	}

}
