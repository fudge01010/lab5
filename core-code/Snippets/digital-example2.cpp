/**
 ============================================================================
 * @file digital-example1.cpp
 * @brief Basic digital input/output example
 *
 *  Created on: 10/1/2016
 *      Author: podonoghue
 ============================================================================
 */
#include <stdio.h>
#include "system.h"
#include "derivative.h"
#include "hardware.h"

using namespace USBDM;

/*
 * Simple Digital I/O example
 *
 * Echoes an external switch to an external LED
 * Uses arduino aliases if available
 *
 *  Switch + LED
 *  1 x Digital input
 *  1 x Digital output
 *
 */

// Connection mapping - change as required
using Switch =   USBDM::GpioB<0,ActiveLow>;
using Led    =   USBDM::GpioB<1,ActiveLow>;

int main(void) {
   Led::setOutput(PinDriveStrength_High);
   Switch::setInput(PinPull_Up);

   for(;;) {
      Led::write(!Switch::read());
   }
}
