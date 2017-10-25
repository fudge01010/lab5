///*
// ============================================================================
// * @file    ux.cpp

// * @brief   Draw UX for RTC
// *
// *  Created on: 12/10/2017
// *      Author: kainburgemeister
// ============================================================================
// */
#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
//#include "system.h"
#include "lcd.h"
#include "spi.h"
#include "delay.h"
#include "hardware.h"
#include "i2c.h"
#include "ux.h"
#include "main.h"

// Allow access to USBDM methods without USBDM:: prefix
using namespace USBDM;

/* **************************************************
 *  Globally shared objects representing hardware
 * ************************************************ */

// SPI interface
Spi0 spi;

// LCD interface using SPI
Lcd lcd(spi);

// I2C interface
I2c0     i2c0;

/* ************************************************** */

/// LCD derived dimensions
static constexpr int LCD_WIDTH  = (LCD_X_MAX-LCD_X_MIN);
static constexpr int LCD_HEIGHT = (LCD_Y_MAX-LCD_Y_MIN);
static constexpr int CENTRE_X   = ((LCD_X_MAX-LCD_X_MIN)/2);
static constexpr int CENTRE_Y   = ((LCD_Y_MAX-LCD_Y_MIN)/2);

// Colour for LCD background
static constexpr int BACKGROUND_COLOUR = (BLACK);

// Colour for LCD foreground
static constexpr int FOREGROUND_COLOUR = (WHITE);

const char* intToChar (int8_t time) {
	switch(time) {
			case 0:
				return "00";
				break;
			case 1:
				return "01";
				break;
			case 2:
				return "02";
				break;
			case 3:
				return "03";
				break;
			case 4:
				return "04";
				break;
			case 5:
				return "05";
				break;
			case 6:
				return "06";
				break;
			case 7:
				return "07";
				break;
			case 8:
				return "08";
				break;
			case 9:
				return "09";
				break;
			case 10:
				return "10";
				break;
			case 11:
				return "11";
				break;
			case 12:
				return "12";
				break;
			case 13:
				return "13";
				break;
			case 14:
				return "14";
				break;
			case 15:
				return "15";
				break;
			case 16:
				return "16";
				break;
			case 17:
				return "17";
				break;
			case 18:
				return "18";
				break;
			case 19:
				return "19";
				break;
			case 20:
				return "20";
				break;
			case 21:
				return "21";
				break;
			case 22:
				return "22";
				break;
			case 23:
				return "23";
				break;
			case 24:
				return "24";
				break;
			case 25:
				return "25";
				break;
			case 26:
				return "26";
				break;
			case 27:
				return "27";
				break;
			case 28:
				return "28";
				break;
			case 29:
				return "29";
				break;
			case 30:
				return "30";
				break;
			case 31:
				return "31";
				break;
			case 32:
				return "32";
				break;
			case 33:
				return "33";
				break;
			case 34:
				return "34";
				break;
			case 35:
				return "35";
				break;
			case 36:
				return "36";
				break;
			case 37:
				return "37";
				break;
			case 38:
				return "38";
				break;
			case 39:
				return "39";
				break;
			case 40:
				return "40";
				break;
			case 41:
				return "41";
				break;
			case 42:
				return "42";
				break;
			case 43:
				return "43";
				break;
			case 44:
				return "44";
				break;
			case 45:
				return "45";
				break;
			case 46:
				return "46";
				break;
			case 47:
				return "47";
				break;
			case 48:
				return "48";
				break;
			case 49:
				return "49";
				break;
			case 50:
				return "50";
				break;
			case 51:
				return "51";
				break;
			case 52:
				return "52";
				break;
			case 53:
				return "53";
				break;
			case 54:
				return "54";
				break;
			case 55:
				return "55";
				break;
			case 56:
				return "56";
				break;
			case 57:
				return "57";
				break;
			case 58:
				return "58";
				break;
			case 59:
				return "59";
				break;
			default:
				return "00";
				break;
		}
}

//Draws cursor (is the sickest) on screen
void drawTimeScreen(timeData currentTime) {
//	0,0 bottom left with ribbon cable upwards

//	int8_t hr = currentTime->hr;
//	char* hr = 0;
//	sprintf(hr, "%d", h);

//  lcd.putStr("Memes", 30, 10, largeFont, FOREGROUND_COLOUR, PINK);

	//Centre Position
//	lcd.drawLine(CENTRE_X+100, CENTRE_Y, CENTRE_X-100, CENTRE_Y, RED);
//	lcd.drawLine(CENTRE_X, CENTRE_Y+100, CENTRE_X, CENTRE_Y-100, RED);

	//Bottom
	lcd.drawLine(CENTRE_X-50, CENTRE_Y-30, CENTRE_X+50, CENTRE_Y-30, WHITE);
	//Left
	lcd.drawLine(CENTRE_X-50, CENTRE_Y-30, CENTRE_X-50, CENTRE_Y+30, WHITE);
	//Top
	lcd.drawLine(CENTRE_X-50, CENTRE_Y+30, CENTRE_X+50, CENTRE_Y+30, WHITE);
	//Right
	lcd.drawLine(CENTRE_X+50, CENTRE_Y+30, CENTRE_X+50, CENTRE_Y-30, WHITE);

	//TimeHours
    lcd.putStr(intToChar(currentTime.hr), CENTRE_X-32, CENTRE_Y-8, largeFont, FOREGROUND_COLOUR, BACKGROUND_COLOUR);

    //DotDot
    lcd.putStr(":", CENTRE_X-16, CENTRE_Y-8, largeFont, FOREGROUND_COLOUR, BACKGROUND_COLOUR);

    //TimeMinutes
    lcd.putStr(intToChar(currentTime.min), CENTRE_X-8, CENTRE_Y-8, largeFont, FOREGROUND_COLOUR, BACKGROUND_COLOUR);

    //DotDot
    lcd.putStr(":", CENTRE_X+8, CENTRE_Y-8, largeFont, FOREGROUND_COLOUR, BACKGROUND_COLOUR);

    //TimeSeconds
    lcd.putStr(intToChar(currentTime.sec), CENTRE_X+16, CENTRE_Y-8, largeFont, FOREGROUND_COLOUR, BACKGROUND_COLOUR);
}

void drawSettingsScreen () {
	//Bottom
	lcd.drawLine(CENTRE_X-60, CENTRE_Y-60, CENTRE_X+60, CENTRE_Y-60, WHITE);
	//Left
	lcd.drawLine(CENTRE_X-60, CENTRE_Y-60, CENTRE_X-60, CENTRE_Y+60, WHITE);
	//Top
	lcd.drawLine(CENTRE_X-60, CENTRE_Y+60, CENTRE_X+60, CENTRE_Y+60, WHITE);
	//Right
	lcd.drawLine(CENTRE_X+60, CENTRE_Y+60, CENTRE_X+60, CENTRE_Y-60, WHITE);

	lcd.putStr("Live Time", CENTRE_X-36, CENTRE_Y+35, largeFont, FOREGROUND_COLOUR, BACKGROUND_COLOUR);

	lcd.putStr("Alarm Clock", CENTRE_X-44, CENTRE_Y+16, largeFont, FOREGROUND_COLOUR, BACKGROUND_COLOUR);

	lcd.putStr("Stop Watch", CENTRE_X-36, CENTRE_Y-4, largeFont, FOREGROUND_COLOUR, BACKGROUND_COLOUR);

	lcd.putStr("Bangers", CENTRE_X-28, CENTRE_Y-24, largeFont, FOREGROUND_COLOUR, BACKGROUND_COLOUR);

	lcd.putStr("Settings", CENTRE_X-32, CENTRE_Y-40, largeFont, FOREGROUND_COLOUR, BACKGROUND_COLOUR);


}

void drawAlarmScreen (timeData currentTime) {
//	0,0 bottom left with ribbon cable upwards

//  lcd.putStr("Memes", 30, 10, largeFont, FOREGROUND_COLOUR, PINK);

	//Centre Position
//	lcd.drawLine(CENTRE_X+100, CENTRE_Y, CENTRE_X-100, CENTRE_Y, RED);
//	lcd.drawLine(CENTRE_X, CENTRE_Y+100, CENTRE_X, CENTRE_Y-100, RED);

	//Bottom
	lcd.drawLine(CENTRE_X-50, CENTRE_Y-30, CENTRE_X+50, CENTRE_Y-30, WHITE);
	//Left
	lcd.drawLine(CENTRE_X-50, CENTRE_Y-30, CENTRE_X-50, CENTRE_Y+30, WHITE);
	//Top
	lcd.drawLine(CENTRE_X-50, CENTRE_Y+30, CENTRE_X+50, CENTRE_Y+30, WHITE);
	//Right
	lcd.drawLine(CENTRE_X+50, CENTRE_Y+30, CENTRE_X+50, CENTRE_Y-30, WHITE);


	//TimeHours
	lcd.putStr(intToChar(currentTime.hr), CENTRE_X-32, CENTRE_Y-8, largeFont, FOREGROUND_COLOUR, BACKGROUND_COLOUR);

	//DotDot
	lcd.putStr(":", CENTRE_X-16, CENTRE_Y-8, largeFont, FOREGROUND_COLOUR, BACKGROUND_COLOUR);

	//TimeMinutes
	lcd.putStr(intToChar(currentTime.min), CENTRE_X-8, CENTRE_Y-8, largeFont, FOREGROUND_COLOUR, BACKGROUND_COLOUR);

	//DotDot
	lcd.putStr(":", CENTRE_X+8, CENTRE_Y-8, largeFont, FOREGROUND_COLOUR, BACKGROUND_COLOUR);

	//TimeSeconds
	lcd.putStr(intToChar(currentTime.sec), CENTRE_X+16, CENTRE_Y-8, largeFont, FOREGROUND_COLOUR, BLUE);
}

void drawTimeSetScreen(struct timeData *currentTime, struct timeSetData setData) {
//	0,0 bottom left with ribbon cable upwards

//	int8_t hr = currentTime->hr;
//	char* hr = 0;
//	sprintf(hr, "%d", h);

//  lcd.putStr("Memes", 30, 10, largeFont, FOREGROUND_COLOUR, PINK);

	//Centre Position
//	lcd.drawLine(CENTRE_X+100, CENTRE_Y, CENTRE_X-100, CENTRE_Y, RED);
//	lcd.drawLine(CENTRE_X, CENTRE_Y+100, CENTRE_X, CENTRE_Y-100, RED);

	//Bottom
	lcd.drawLine(CENTRE_X-50, CENTRE_Y-30, CENTRE_X+50, CENTRE_Y-30, WHITE);
	//Left
	lcd.drawLine(CENTRE_X-50, CENTRE_Y-30, CENTRE_X-50, CENTRE_Y+30, WHITE);
	//Top
	lcd.drawLine(CENTRE_X-50, CENTRE_Y+30, CENTRE_X+50, CENTRE_Y+30, WHITE);
	//Right
	lcd.drawLine(CENTRE_X+50, CENTRE_Y+30, CENTRE_X+50, CENTRE_Y-30, WHITE);

	 //DotDot HH:MM
	lcd.putStr(":", CENTRE_X-16, CENTRE_Y-8, largeFont, FOREGROUND_COLOUR, BACKGROUND_COLOUR);
	//DotDot MM:SS
	lcd.putStr(":", CENTRE_X+8, CENTRE_Y-8, largeFont, FOREGROUND_COLOUR, BACKGROUND_COLOUR);

	//TimeHours
	if (setData.cursor == 0) {
		//draw the kerser here
		lcd.putStr(intToChar(currentTime->hr), CENTRE_X-32, CENTRE_Y-8, largeFont, BLACK, WHITE);
	} else {
		lcd.putStr(intToChar(currentTime->hr), CENTRE_X-32, CENTRE_Y-8, largeFont, FOREGROUND_COLOUR, BACKGROUND_COLOUR);
	}

	//TimeMinutes
	if (setData.cursor == 1) {
		//draw the kerser here
		lcd.putStr(intToChar(currentTime->min), CENTRE_X-32, CENTRE_Y-8, largeFont, BLACK, WHITE);
	} else {
		lcd.putStr(intToChar(currentTime->min), CENTRE_X-32, CENTRE_Y-8, largeFont, FOREGROUND_COLOUR, BACKGROUND_COLOUR);
	}

    //TimeSeconds
	if (setData.cursor == 3) {
		//draw the kerser here
		lcd.putStr(intToChar(currentTime->sec), CENTRE_X-32, CENTRE_Y-8, largeFont, BLACK, WHITE);
	} else {
		lcd.putStr(intToChar(currentTime->sec), CENTRE_X-32, CENTRE_Y-8, largeFont, FOREGROUND_COLOUR, BACKGROUND_COLOUR);
	}
}
