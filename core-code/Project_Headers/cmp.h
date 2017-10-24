/**
 * @file     cmp.h (180.ARM_Peripherals/Project_Headers/cmp.h)
 * @brief    Voltage Comparator
 *
 * @version  V4.12.1.80
 * @date     13 April 2016
 */

#ifndef PROJECT_HEADERS_CMP_H_
#define PROJECT_HEADERS_CMP_H_
 /*
 * *****************************
 * *** DO NOT EDIT THIS FILE ***
 * *****************************
 *
 * This file is generated automatically.
 * Any manual changes will be lost.
 */
#include "derivative.h"
#include "hardware.h"

namespace USBDM {
/**
 * @addtogroup CMP_Group CMP, Analogue Comparator
 * @brief Pins used for Analogue Comparator
 * @{
 */

enum Cmp0Input {
   Cmp0Input_CmpIn0  = 0, //!< Cmp external pin 0
   Cmp0Input_CmpIn1  = 1, //!< Cmp external pin 1
   Cmp0Input_CmpIn2  = 2, //!< Cmp external pin 2
   Cmp0Input_CmpIn3  = 3, //!< Cmp external pin 3
   Cmp0Input_CmpIn4  = 4, //!< Cmp external pin 4
   Cmp0Input_VRefOut = 5, //!< Vref Output
   Cmp0Input_Bandgap = 6, //!< Internal Band-gap
   Cmp0Input_Dac0Ref = 7, //!< 6-bit dac0 reference
};

enum Cmp1Input {
   Cmp1Input_CmpIn0  = 0, //!< Cmp external pin 0
   Cmp1Input_CmpIn1  = 1, //!< Cmp external pin 1
   Cmp1Input_VRefOut = 5, //!< Vref Output
   Cmp1Input_Bandgap = 6, //!< Internal Band-gap
   Cmp1Input_Dac1Ref = 7, //!< 6-bit dac1 reference
};

enum CmpFilter {
   CmpFilter_None = CMP_CR0_FILTER_CNT(0), //!< No filtering - Illegal when sampling is enabled.
   CmpFilter_1    = CMP_CR0_FILTER_CNT(1), //!< 1 sample must agree
   CmpFilter_2    = CMP_CR0_FILTER_CNT(2), //!< 2 samples must agree
   CmpFilter_3    = CMP_CR0_FILTER_CNT(3), //!< 3 samples must agree
   CmpFilter_4    = CMP_CR0_FILTER_CNT(4), //!< 4 samples must agree
   CmpFilter_5    = CMP_CR0_FILTER_CNT(5), //!< 5 samples must agree
   CmpFilter_6    = CMP_CR0_FILTER_CNT(6), //!< 6 samples must agree
   CmpFilter_7    = CMP_CR0_FILTER_CNT(7), //!< 7 samples must agree
};

enum CmpHysteresis {
   CmpHysteresis_0 = CMP_CR0_HYSTCTR(0), //!< Minimum.
   CmpHysteresis_1 = CMP_CR0_HYSTCTR(1),
   CmpHysteresis_2 = CMP_CR0_HYSTCTR(2),
   CmpHysteresis_3 = CMP_CR0_HYSTCTR(3), //!< Maxiimum.
};

/**
 * Comparator interrupt edge
 */
enum CmpInterrupt {
   CmpInterrupt_None    = CMP_SCR_IER(0)|CMP_SCR_IEF(0),  //!< Rising edge
   CmpInterrupt_Rising  = CMP_SCR_IER(1)|CMP_SCR_IEF(0),  //!< Rising edge
   CmpInterrupt_Falling = CMP_SCR_IER(0)|CMP_SCR_IEF(1),  //!< Falling edge
   CmpInterrupt_Both    = CMP_SCR_IER(1)|CMP_SCR_IEF(1),  //!< Rising or falling edge
};

/**
 * Type definition for CMP interrupt call back
 *
 * @param[in]  status Flags indicating interrupt source (CMP_SCR_CFR_MASK, CMP_SCR_CFF_MASK)
 */
typedef void (*CMPCallbackFunction)(int status);

/**
 * Template class representing a Voltage Reference
 *
 * @tparam info      Information class for CMP
 *
 * @code
 *  // Example using an interrupt handler on both rising and falling edges
 *
 *  // Connections - change as required
 *  using Cmp = USBDM::Cmp0;
 *
 *  Cmp::enable();
 *  Cmp::configure();
 *  Cmp::setDacLevel(20);
 *  Cmp::setCallback(callback);
 *  Cmp::enableFallingEdgeInterrupts(true);
 *  Cmp::enableRisingEdgeInterrupts(true);
 *
 * @endcode
 */
template<class Info>
class CmpBase_T {

protected:
   static constexpr volatile CMP_Type *cmp      = Info::cmp;
   static constexpr volatile uint32_t *clockReg = Info::clockReg;

public:
   /**
    * Basic enable CMP\n
    * Includes configuring all pins
    */
   static void enable() {
      // Configure pins
      Info::initPCRs();

      // Enable clock to CMP interface
      *clockReg |= Info::clockMask;
   }

   /**
    * Enable with default settings\n
    * Includes configuring all pins
    */
   static void configure() {
      enable();

      // Initialise hardware
      cmp->CR0   = Info::cr0;
      cmp->CR1   = Info::cr1 | CMP_CR1_EN_MASK;
      cmp->FPR   = Info::fpr;
      cmp->SCR   = Info::scr;
      cmp->DACCR = Info::daccr;
      cmp->MUXCR = Info::muxcr;

      enableNvicInterrupts();
   }

   /**
    * Disable Cmp
    */
   static void disable() {
      cmp->CR1 = 0;
      *clockReg &= ~Info::clockMask;
   }

   /**
    * Enable/disable interrupts in NVIC
    *
    * @param[in]  enable true to enable, false to disable
    */
   static void enableNvicInterrupts(bool enable=true) {

      if (enable) {
         // Enable interrupts
         NVIC_EnableIRQ(Info::irqNums[0]);

         // Set priority level
         NVIC_SetPriority(Info::irqNums[0], Info::irqLevel);
      }
      else {
         // Disable interrupts
         NVIC_DisableIRQ(Info::irqNums[0]);
      }
   }

   /**
    * Enable/disable edge interrupts
    *
    * @param[in]  cmpInterrupt Control edge selection
    */
   static void enableInterrupts(CmpInterrupt cmpInterrupt) {
      cmp->SCR = (cmp->SCR&~(CMP_SCR_IER(1)|CMP_SCR_IEF(1)))|cmpInterrupt;
   }

   /**
    * Enable/disable rising edge interrupts
    *
    * @param[in]  enable True=>enable, False=>disable
    */
   static void enableRisingEdgeInterrupts(bool enable=true) {
      if (enable) {
         cmp->SCR |= CMP_SCR_IER_MASK;
      }
      else {
         cmp->SCR &= ~CMP_SCR_IER_MASK;
      }
   }

   /**
    * Enable/disable falling edge interrupts
    *
    * @param[in]  enable True=>enable, False=>disable
    */
   static void enableFallingEdgeInterrupts(bool enable=true) {
      if (enable) {
         cmp->SCR |= CMP_SCR_IEF_MASK;
      }
      else {
         cmp->SCR &= ~CMP_SCR_IEF_MASK;
      }
   }

   /**
    * Enable/disable DMA requests
    *
    * @param[in]  enable True=>enable, False=>disable
    */
   static void enableDmaRequests(bool enable=true) {
      if (enable) {
         cmp->SCR |= CMP_SCR_DMAEN_MASK;
      }
      else {
         cmp->SCR &= ~CMP_SCR_DMAEN_MASK;
      }
   }

   /**
    * Clear edge interrupt flags
    */
   static void clearInterruptFlags() {
      cmp->SCR |= CMP_SCR_CFR_MASK|CMP_SCR_CFF_MASK;
   }

   /**
    * Configure DAC
    *
    * @param[in]  level  DAC level to select (0..63)
    * @param[in]  source Reference source select (0..1) Usually 0=>Vin, 1=>Vdd
    * @param[in]  enable True=>enable, False=>disable
    */
   static void setDacLevel(uint8_t level, uint8_t source=(Info::daccr&CMP_DACCR_VRSEL_MASK)?1:0, bool enable=true) {
      cmp->DACCR = CMP_DACCR_DACEN(enable)|CMP_DACCR_VRSEL(source)|CMP_DACCR_VOSEL(level);
   }

   /**
    * Configure Comparator input sources
    *
    * @param[in]  positiveInput (0..7) (7 => DAC)
    * @param[in]  negativeInput (0..7) (7 => DAC)
    */
   static void selectInputs(uint8_t positiveInput, uint8_t negativeInput) {
      //! MUX Control Register
      cmp->MUXCR =
         CMP_MUXCR_PSEL(positiveInput)| // Plus Input Mux Control
         CMP_MUXCR_MSEL(negativeInput); // Minus Input Mux Control
   }

   /**
    * Set input filtering and hysteresis
    *
    * @param[in] cmpFilter       Filtering clock pulses
    * @param[in] cmpHysteresis   Hysteresis level
    */
   static void setInputConditioning(CmpFilter cmpFilter, CmpHysteresis cmpHysteresis) {
      cmp->CR0 = cmpFilter|cmpHysteresis;
   }
};

/**
 * Template class to provide CMP callback
 */
template<class Info>
class CmpIrq_T : public CmpBase_T<Info> {

protected:
   /** Callback function for ISR */
   static CMPCallbackFunction callback;

public:
   /**
    * IRQ handler
    */
   static void irqHandler() {
      int status = CmpBase_T<Info>::cmp->SCR&(CMP_SCR_CFR_MASK|CMP_SCR_CFF_MASK);
      // Clear interrupt
      CmpBase_T<Info>::cmp->SCR |= status;
      if (callback != 0) {
         callback(status);
      }
      else {
         setAndCheckErrorCode(E_NO_HANDLER);
      }
   }

   /**
    * Set callback function
    *
    * @param[in]  theCallback Callback function to execute on interrupt
    */
   static void setCallback(CMPCallbackFunction theCallback) {
      callback = theCallback;
   }
};

template<class Info> CMPCallbackFunction CmpIrq_T<Info>::callback = 0;

#if defined(USBDM_CMP_IS_DEFINED)
using Cmp = CmpIrq_T<CmpInfo>;
#endif

#if defined(USBDM_CMP0_IS_DEFINED)
using Cmp0 = CmpIrq_T<Cmp0Info>;
#endif

#if defined(USBDM_CMP1_IS_DEFINED)
using Cmp1 = CmpIrq_T<Cmp1Info>;
#endif

#if defined(USBDM_CMP2_IS_DEFINED)
using Cmp2 = CmpIrq_T<Cmp2Info>;
#endif

#if defined(USBDM_CMP3_IS_DEFINED)
using Cmp3 = CmpIrq_T<Cmp3Info>;
#endif
/**
 * @}
 */
} // End namespace USBDM

#endif /* PROJECT_HEADERS_CMP_H_ */
