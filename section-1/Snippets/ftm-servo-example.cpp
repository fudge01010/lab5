/**
 ============================================================================
 * @file    ftm-servo-example.cpp (180.ARM_Peripherals)
 * @brief   Demo using Ftm class to implement a servo-motor controller
 *
 *  Created on: 10/6/2016
 *      Author: podonoghue
 ============================================================================
 */
#include <stdio.h>
#include "system.h"
#include "derivative.h"
#include "hardware.h"

using namespace USBDM;

/**
 * Class representing a servo motor connected to a FTM channel
 * Note that all FTM channels will be set to same period
 *
 * @tparam FtmChannel Class representing a FTM channel e.g. Ftm0Channel<3>
 */
template <class FtmChannel>
class Servo {

private:
   // Assumes servo is controlled by a [1,2] millisecond pulse repeated every 20 millisecond
   static constexpr float SERVO_PERIOD = 20.0 * ms;
   static constexpr float SERVO_MIN    =  1.0 * ms;
   static constexpr float SERVO_MAX    =  2.0 * ms;

public:
   /**
    * Enable servo
    * Position is centred
    */
   static void enable() {
      FtmChannel::enable();
      FtmChannel::setDriveStrength(PinDriveStrength_High);
      FtmChannel::setPeriod(SERVO_PERIOD);
      FtmChannel::setHighTime((SERVO_MIN+SERVO_MAX)/2);
   }

   /**
    * Set position
    *
    * @param position Position as an angle 0-180
    */
   static ErrorCode setPosition(int position) {
      if ((position<0) || (position>180)) {
         return setErrorCode(E_ILLEGAL_PARAM);
      }
      return FtmChannel::setHighTime(SERVO_MIN+((position/180.0f)*(SERVO_MAX-SERVO_MIN)));
   }
};

// Instantiate servo on pin
// It will be necessary to map the pin to a FTM channel in Configure.usbdmProject
//using servo = Servo<ftm_D2>;
using servo = Servo<Ftm0Channel<7>>;

int main() {
   printf("Starting\n");

   printf("SystemBusClock  = %ld\n", ::SystemBusClock);
   printf("SystemCoreClock = %ld\n", ::SystemCoreClock);

   servo::enable();

   // Check if configuration failed
   USBDM::checkError();

   for (;;) {
      for(int i=0;i<=180;i++) {
         servo::setPosition(i);
         waitMS(50);
         printf("Position = %d\n", i);
      }
   }
   return 0;
}