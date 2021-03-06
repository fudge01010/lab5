/**
 * @file     pca9685.h
 * @brief    Interface for PCA9685 PWM controller
 *
 * @version  V4.12.1.50
 * @date     18 June 2015
 */

#ifndef INCLUDE_USBDM_PCA9685_H
#define INCLUDE_USBDM_PCA9685_H
 /*
 * *****************************
 * *** DO NOT EDIT THIS FILE ***
 * *****************************
 *
 * This file is generated automatically.
 * Any manual changes will be lost.
 */
#include <stdint.h>
#include <stddef.h>
#include "i2c.h"

namespace USBDM {

/**
 * @addtogroup PCA9685_Group PCA9685 PWM controller
 * @brief C++ Class providing interface to PCA9685
 * @{
 */

// Default address of first (only) motor board
constexpr uint32_t  PCA9685_DEFAULT_SLAVE_BASE_ADDRESS  = ((uint8_t)(0x60<<1)); // PCA9685 Slave address

// Mode register 1, MODE1
constexpr uint32_t  PCA9685_MODE1_RESTART_MASK  =  (1<<7); // 0*/1 => Shows state of RESTART logic.
constexpr uint32_t  PCA9685_MODE1_EXTCLK_MASK   =  (1<<6); // 0*/1 => Use internal/EXTCLK pin clock.
constexpr uint32_t  PCA9685_MODE1_AI_MASK       =  (1<<5); // 0*/1 => Register Auto-Increment enable/disabled.
constexpr uint32_t  PCA9685_MODE1_SLEEP_MASK    =  (1<<4); // 0/1* => Low power mode on/off (Oscillator on/off)
constexpr uint32_t  PCA9685_MODE1_SUB1_MASK     =  (1<<3); // 0/1* => PCA9685 responds to I2C-bus sub-address 1.
constexpr uint32_t  PCA9685_MODE1_SUB2_MASK     =  (1<<2); // 0/1* => PCA9685 responds to I2C-bus sub-address 1.
constexpr uint32_t  PCA9685_MODE1_SUB3_MASK     =  (1<<1); // 0/1* => PCA9685 responds to I2C-bus sub-address 1.
constexpr uint32_t  PCA9685_MODE1_ALLCALL_MASK  =  (1<<0); // 0/1* => Does not/does respond to LED All Call I2C-bus address.

// Mode register 2, MODE2
constexpr uint32_t  PCA9685_MODE2_INVRT_MASK   =   (1<<4); // 0*   => Output logic state not inverted. Value to use when external driver used.
//                                           //         Applicable when OE = 0.
//                                           // 1    => Output logic state inverted. Value to use when no external driver used.
//                                           //         Applicable when OE = 0.
constexpr uint32_t  PCA9685_MODE2_OCH_MASK     =   (1<<3); // 0*   => Outputs change on STOP command.
//                                           // 1    => Outputs change on ACK.
constexpr uint32_t  PCA9685_MODE2_OUTDRV_MASK  =   (1<<2); // 0    => The 16 LEDn outputs are configured with an open-drain structure.
//                                           // 1*   => The 16 LEDn outputs are configured with a totem pole structure.
constexpr uint32_t  PCA9685_MODE2_OUTNE_MASK   =   (3<<0); // 00*  => When OE = 1 (output drivers not enabled), LEDn = 0.
//                                           // 01   => When OE = 1 (output drivers not enabled):
//                                           //         LEDn = 1 when OUTDRV = 1
//                                           //         LEDn = high-impedance when OUTDRV = 0 (same as OUTNE[1:0] = 10)
//                                           // 1X   => When OE = 1 (output drivers not enabled), LEDn = high-impedance.

// Default PWM oscillator parameters
constexpr uint32_t  PCA9685_OSC_CLOCK_FREQ         = (25000000UL);
constexpr uint32_t  PCA9685_PWM_FREQ               = (200UL);
constexpr uint32_t  PCA9685_DEFAULT_OSC_PRESCALE   = (((PCA9685_OSC_CLOCK_FREQ+2048UL*PCA9685_PWM_FREQ)/(4096UL*PCA9685_PWM_FREQ))-1);

/**
 * @brief Class interfacing a PCA9685 PWM controller chip (such as on the Adafruit motor driver board)
 *
 * <b>Example</b>
 * @code
 *
 *    USBDM::I2c *i2c = new USBDM::I2c0();
 *    USBDM::PCA9685 *pca9685= new USBDM::PCA9685(i2c);
 *
 *    pca9685->set_pin_high(3);
 *    pca9685->set_pin_pwm(3, 50);
 *
 * @endcode
 *
 */
class PCA9685 {

private:
   static const int MAX_PWM = 4095;

   I2c     &i2c;
   uint8_t  slaveAddress;

public:
   /**
    * Constructor with default values
    *
    * <b>Example</b>
    * @code
    *  USBDM::I2c *i2c = new USBDM::I2c0();
    *  USBDM::PCA9685 *pca9685= new USBDM::PCA9685(i2c);
    * @endcode
    *
    * @param i2c           - The I2C interface to use
    * @param deviceAddress - Slave device address (PCA9685_DEFAULT_SLAVE_BASE_ADDRESS+0,1,2,3)
    * @param prescaleValue - Clock pre-scaler
    * @param mode1Value    - Mode 1 value (use PCA9685_MODE1_x macros)
    * @param mode2Value    - Mode 2 value (use PCA9685_MODE2_x macros)
    */
   PCA9685(I2c &i2c,
         uint8_t  deviceAddress = PCA9685_DEFAULT_SLAVE_BASE_ADDRESS,
         uint8_t  prescaleValue = PCA9685_DEFAULT_OSC_PRESCALE,
         uint8_t  mode1Value    = PCA9685_MODE1_AI_MASK,
         uint8_t  mode2Value    = PCA9685_MODE2_OUTDRV_MASK
   );
   /**
    * Set all outputs low
    */
   void allLow(void);
   /**
    * Set all outputs high
    */
   void allHigh(void);
   /**
    * Sets the dutyCycle of the given pin
    *
    * @param pinNum     Pin to modify (0-15)
    * @param dutyCycle  Duty-cycle to set. Expressed as a value [0..4095]
    *
    */
   void set_pin_pwm(unsigned pinNum, unsigned dutyCycle);
   /**
    * Set given pin high
    *
    * @param pinNum     Pin to modify (0-15)
    */
   void set_pin_high(unsigned pinNum);
   /**
    * Set given pin low
    *
    * @param pinNum     Pin to modify (0-15)
    */
   void set_pin_low(unsigned pinNum);
};

/**
 * @}
 */

} // End namespace USBDM

#endif /* INCLUDE_USBDM_PCA9685_H */
