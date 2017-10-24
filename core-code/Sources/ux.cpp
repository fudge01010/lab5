///*
// ============================================================================
// * @file    ux.cpp
// * @brief   Draw UX for RTC
// *
// *  Created on: 12/10/2017
// *      Author: kainburgemeister
// ============================================================================
// */
//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include "system.h"
#include "lcd.h"
#include "spi.h"
#include "delay.h"
#include "hardware.h"
#include "i2c.h"
#include "ux.h"

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


//Draws cursor (is the sickest) on screen
void drawTimeScreen(time *currentTime) {
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
    lcd.putStr("12", CENTRE_X-32, CENTRE_Y-8, largeFont, FOREGROUND_COLOUR, BACKGROUND_COLOUR);

    //DotDot
    lcd.putStr(":", CENTRE_X-16, CENTRE_Y-8, largeFont, FOREGROUND_COLOUR, BACKGROUND_COLOUR);

    //TimeMinutes
    lcd.putStr("00", CENTRE_X-8, CENTRE_Y-8, largeFont, FOREGROUND_COLOUR, BACKGROUND_COLOUR);

    //DotDot
    lcd.putStr(":", CENTRE_X+8, CENTRE_Y-8, largeFont, FOREGROUND_COLOUR, BACKGROUND_COLOUR);

    //TimeSeconds
    lcd.putStr("00", CENTRE_X+16, CENTRE_Y-8, largeFont, FOREGROUND_COLOUR, BACKGROUND_COLOUR);
}




