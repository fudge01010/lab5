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
static constexpr int PIT_FREQUENCY = 2;

static SwitchValue lastSwitch = noSwitch;
static volatile struct buttonState buttonData;

/**
 * Get switch names for printing
 *
 * @param switchValue Value to look up
 *
 * @return Switch value as string
 */
static const char *getSwitchName(SwitchValue switchValue) {

	static const char *switchNames[] = {
	      "noSwitch",
		  "northSwitch",
	      "eastSwitch",
	      "southSwitch",
	      "westSwitch",
	      "centreSwitch",
	   };

   if (switchValue>=(sizeof(switchNames)/sizeof(switchNames[0]))) {
      return "Illegal switch value";
   }
   return switchNames[switchValue];
}


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
	   printf("yaaas\n");
   }
   if (currentSwitch == noSwitch && buttonData.triggered)
	   buttonData.triggered = false;
   lastSwitch = currentSwitch;

}


void configure5wayInterrupt(buttonState *swState) {
	//do some stuff yo

   buttonState &buttonData = *swState;
   buttonData.triggered = false;
   buttonData.direction = southSwitch;
//	buttonData->triggered = true;

   EastSwitch::setInput(PinPull_Up, PinIrq_None, PinFilter_Passive);
   SouthSwitch::setInput(PinPull_Up, PinIrq_None, PinFilter_Passive);
   WestSwitch::setInput(PinPull_Up, PinIrq_None, PinFilter_Passive);
   CentreSwitch::setInput(PinPull_Up, PinIrq_None, PinFilter_Passive);
   NorthSwitch::setInput(PinPull_Up, PinIrq_None, PinFilter_Passive);

   // Do default configure
   Pit::configure();

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

//void switchTest() {
//
////   for(;;) {
//      // Report switch changes
//      SwitchValue currentSwitch = switchValue;
////      printf("Changed #%d\n", currentSwitch);
//      if ((currentSwitch != lastSwitch) && (currentSwitch != noSwitch)) {
//         printf("Changed #%s\n", getSwitchName(currentSwitch));
//      }
//      lastSwitch = currentSwitch;
////   }
////
////   return 0;
//}
