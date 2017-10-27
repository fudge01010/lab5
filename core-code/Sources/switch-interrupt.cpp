/**
 * @file pit-example3-MK.cpp
 */
#include <stdio.h>
#include "hardware.h"
#include "main.h"
#include "pit.h"
#include "switch-interrupt.h"

using namespace USBDM;

// Jog switch on LCD board
using EastSwitch   = USBDM::GpioC<0,ActiveLow>;
using SouthSwitch  = USBDM::GpioC<1,ActiveLow>;
using WestSwitch   = USBDM::GpioD<6,ActiveLow>;
using CentreSwitch = USBDM::GpioD<5,ActiveLow>;
using NorthSwitch  = USBDM::GpioB<1,ActiveLow>;

// Debounced switch value
static volatile SwitchValue switchValue = noSwitch;

// PIT frequency (Hz)
static constexpr int PIT_FREQUENCY = 100;

static SwitchValue lastSwitch = noSwitch;
static buttonState buttonData;


/*
 * This callback is set programmatically
 *
 * It polls the switch and provides a debounced result in switchValue
 */
void deBouncer() {
   // Encode all switch values as a single binary number
   int swInt =
      (EastSwitch::read()<<4)|
      (SouthSwitch::read()<<3)|
      (WestSwitch::read()<<2)|
      (CentreSwitch::read()<<1)|
      (NorthSwitch::read()<<0);

   switch (swInt) {
   case 1:
	   switchValue = northSwitch;
	   break;
   case 2:
	   switchValue = centreSwitch;
	   break;
   case 4:
	   switchValue = westSwitch;
	   break;
   case 8:
	   switchValue = southSwitch;
	   break;
   case 16:
	   switchValue = eastSwitch;
	   break;
   default:
	   switchValue = noSwitch;
	   break;
   }


   SwitchValue currentSwitch = switchValue;
//   printf("sw is  #%s\n", getSwitchName(currentSwitch));  //debug print line - V bad as interrupt handler

   if ((currentSwitch != lastSwitch) && (currentSwitch != noSwitch)) {
	   buttonData.triggered = true;
	   buttonData.direction = currentSwitch;
//	   printf("yaaas\n");
   }
   if (currentSwitch == noSwitch && buttonData.triggered)
	   buttonData.triggered = false;
   lastSwitch = currentSwitch;

}

/**
 * Configures all 5-way button interrupts, pins, handlers, etc.
 *
 * @param address of swState variable - not used.
 *
 * @return nil
 */
void configure5wayInterrupt(buttonState *swState) {
	//do some stuff yo

   buttonData.triggered = false;
   buttonData.direction = southSwitch;

   EastSwitch::setInput(PinPull_Up, PinIrq_None, PinFilter_Passive);
   SouthSwitch::setInput(PinPull_Up, PinIrq_None, PinFilter_Passive);
   WestSwitch::setInput(PinPull_Up, PinIrq_None, PinFilter_Passive);
   CentreSwitch::setInput(PinPull_Up, PinIrq_None, PinFilter_Passive);
   NorthSwitch::setInput(PinPull_Up, PinIrq_None, PinFilter_Passive);

   // Do default configure
//   Pit::configure();

   // Set handler for channel 1 programmatically
   Pit::setCallback(1, deBouncer);

   // Setup debouncer to execute every 5 ms (200 Hz)
   Pit::configureChannelInTicks(1, ::SystemBusClock/PIT_FREQUENCY);

   // Enable interrupts on the channel
   Pit::enableInterrupts(1);

//   Pit::enableNvicInterrupts();

   // Check for errors so far
   checkError();
}

/**
 * Returns the state of the debounced buttons
 *
 * @param nil
 *
 * @return buttonState struct - containing button status + button direction enum.
 */
struct buttonState pullFromMem() {
//	return struct buttonState *buttonData;
	return buttonData;
}
