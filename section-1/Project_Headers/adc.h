/**
 * @file     adc.h (180.ARM_Peripherals/Project_Headers/adc.h)
 * @brief    ADC routines
 *
 * @version  V4.12.1.80
 * @date     13 April 2016
 */
#ifndef HEADER_ADC_H
#define HEADER_ADC_H
/*
 * *****************************
 * *** DO NOT EDIT THIS FILE ***
 * *****************************
 *
 * This file is generated automatically.
 * Any manual changes will be lost.
 */
#include <climits>
#include <cstddef>
#include <cassert>
#include "derivative.h"

/*
 * Default port information
 */
#ifndef FIXED_PORT_CLOCK_REG
#define FIXED_PORT_CLOCK_REG SCGC5
#endif

#ifndef ADC0_CLOCK_MASK
#ifdef SIM_SCGC6_ADC0_MASK
#define ADC0_CLOCK_MASK SIM_SCGC6_ADC0_MASK
#define ADC0_CLOCK_REG  SCGC6
#endif
#ifdef SIM_SCGC3_ADC1_MASK
#define ADC1_CLOCK_MASK SIM_SCGC3_ADC1_MASK
#define ADC1_CLOCK_REG  SCGC3
#endif
#ifdef SIM_SCGC6_ADC1_MASK
#define ADC1_CLOCK_MASK SIM_SCGC6_ADC1_MASK
#define ADC1_CLOCK_REG  SCGC6
#endif
#ifdef SIM_SCGC6_ADC2_MASK
#define ADC2_CLOCK_MASK SIM_SCGC6_ADC2_MASK
#define ADC2_CLOCK_REG  SCGC6
#endif
#endif

namespace USBDM {

/**
 * @addtogroup ADC_Group ADC, Analogue Input
 * @brief Abstraction for Analogue Input
 */

/**
 * Default PCR value for pins used as GPIO (including multiplexor value)
 */
static constexpr PcrValue ADC_DEFAULT_PCR = pcrValue(
      PinPull_None, PinDriveStrength_Low, PinDriveMode_PushPull, PinIrq_None, PinFilter_None, PinSlewRate_Fast, PinMux_Analogue);

/**
 * ADC Resolutions\n
 * The resolutions available vary with single-ended/differential modes\n
 * Note the equivalence between modes e.g. 8-bit-se = 9-bit-diff
 */
enum AdcResolution {
   AdcResolution_8bit_se    = ADC_CFG1_MODE(0),  //!<  8-bit unsigned for use with single-ended mode
   AdcResolution_10bit_se   = ADC_CFG1_MODE(2),  //!< 10-bit unsigned for use with single-ended mode
   AdcResolution_12bit_se   = ADC_CFG1_MODE(1),  //!< 12-bit unsigned for use with single-ended mode
   AdcResolution_16bit_se   = ADC_CFG1_MODE(3),  //!< 16-bit unsigned for use with single-ended mode
   AdcResolution_9bit_diff  = ADC_CFG1_MODE(0),  //!<  9-bit signed for use with differential mode
   AdcResolution_11bit_diff = ADC_CFG1_MODE(2),  //!< 11-bit signed for use with differential mode
   AdcResolution_13bit_diff = ADC_CFG1_MODE(1),  //!< 13-bit signed for use with differential mode
   AdcResolution_16bit_diff = ADC_CFG1_MODE(3),  //!< 16-bit signed for use with differential mode
};

/**
 * ADC Averaging
 */
enum AdcAveraging {
   AdcAveraging_off = ADC_SC3_AVGE(0),                                //!< No averaging - single conversion
   AdcAveraging_4   = ADC_SC3_AVGE(1)|ADC_SC3_AVGS(0),                //!< Average across 4 conversions
   AdcAveraging_8   = ADC_SC3_AVGE(1)|ADC_SC3_AVGS(1),                //!< Average across 8 conversions
   AdcAveraging_16  = ADC_SC3_AVGE(1)|ADC_SC3_AVGS(2),                //!< Average across 16 conversions
   AdcAveraging_32  = ADC_SC3_AVGE(1)|ADC_SC3_AVGS(3),                //!< Average across 32 conversions
   AdcAveraging_Cal = ADC_SC3_AVGE(1)|ADC_SC3_AVGS(3)|ADC_SC3_CAL(1), //!< Average across 32 conversions + start calibration
};

/**
 * ADC input clock source.
 */
enum AdcClockSource {
   AdcClockSource_Bus      = ADC_CFG1_ADICLK(0), //!< Bus Clock
   AdcClockSource_Busdiv2  = ADC_CFG1_ADICLK(1), //!< Bus Clock / 2
   AdcClockSource_Alt      = ADC_CFG1_ADICLK(2), //!< Alternate clock (ALTCLK)
   AdcClockSource_Asynch   = ADC_CFG1_ADICLK(3), //!< Asynchronous clock (ADACK Internal ADC clock source)
};

/**
 * ADC clock divider
 */
enum AdcClockDivider {
   AdcClockDivider_1       = ADC_CFG1_ADIV(0), //!< Clock divide by 1
   AdcClockDivider_2       = ADC_CFG1_ADIV(1), //!< Clock divide by 2
   AdcClockDivider_4       = ADC_CFG1_ADIV(2), //!< Clock divide by 3
   AdcClockDivider_8       = ADC_CFG1_ADIV(3), //!< Clock divide by 4
};

/**
 * Controls whether an interrupt is triggered at the end of a conversion
 */
enum AdcInterrupt {
   AdcInterrupt_disable = ADC_SC1_AIEN(0), //!< No interrupt on conversion complete
   AdcInterrupt_enable  = ADC_SC1_AIEN(1), //!< No interrupt on conversion complete
};

/**
 * Select the pretrigger
 */
enum AdcPretrigger {
   AdcPretrigger_0  = 0, //!< Use pretrigger A = SC1[0]/R[0]
   AdcPretrigger_1  = 1, //!< Use pretrigger B = SC1[1]/R[1]
};

/**
 * Select the pretrigger
 */
enum AdcDma {
   AdcDma_Disable = ADC_SC2_DMAEN(0), //!< DMA disabled
   AdcDma_Enable  = ADC_SC2_DMAEN(1), //!< DMA enabled
};

/**
 *  Input sample interval. Long sample times allow the use of higher input impedance sources
 */
enum AdcSample {
   AdcSample_Normal  = ADC_CFG1_ADLSMP(0),                    //!< Normal sample interval
   AdcSample_2       = ADC_CFG1_ADLSMP(1)|ADC_CFG2_ADLSTS(3), //!< Extra 2 sample clocks (6 clocks total)
   AdcSample_6       = ADC_CFG1_ADLSMP(1)|ADC_CFG2_ADLSTS(2), //!< Extra 6 sample clocks (10 clocks total)
   AdcSample_12      = ADC_CFG1_ADLSMP(1)|ADC_CFG2_ADLSTS(1), //!< Extra 12 sample clocks (16 clocks total)
   AdcSample_20      = ADC_CFG1_ADLSMP(1)|ADC_CFG2_ADLSTS(0), //!< Extra 20 sample clocks (24 clocks total)
};

/**
 * Selects between A/B multiplexor inputs on some ADC channels
 */
enum AdcMuxsel {
   AdcMuxsel_A  = ADC_CFG2_MUXSEL(0), //!< The multiplexor selects A channels
   AdcMuxsel_B  = ADC_CFG2_MUXSEL(1), //!< The multiplexor selects B channels
};

/**
 * Allows reduced power consumption but with restricted input clock speed
 */
enum AdcPower {
   AdcPower_Normal  = ADC_CFG1_ADLPC(0), //!< Normal power operation
   AdcPower_Lowl    = ADC_CFG1_ADLPC(1), //!< Low power operation
};

/**
 * Allows higher input clock speed operation.\n
 * This actually extends the number of conversion clock cycles but is offset by allowing a faster input clock.
 */
enum AdcClockRange {
   AdcClockRange_normal = ADC_CFG2_ADHSC(0), //!< Normal input clock range
   AdcClockRange_high   = ADC_CFG2_ADHSC(1), //!< Higher speed input clock range selected
};

/**
 * Controls whether the internal ADC clock is always enabled.\n
 * In any case, if internal clock is selected for use by the converter (AdcClockSource_Asynch) then\n
 * it will be enabled when needed for a conversion but with an extended conversion time.\n
 * If always enable this startup delay is avoided and the clock may be use by other peripherals.
 */
enum AdcAsyncClock {
   AdcAsyncClock_disabled = ADC_CFG2_ADACKEN(0), //!< ADC Asynchronous clock enable on demand.
   AdcAsyncClock_enabled  = ADC_CFG2_ADACKEN(0), //!< ADC Asynchronous clock always enabled
};

/**
 * Selects between single and continuous conversions
 */
enum AdcContinuous {
   AdcContinuous_Disabled = ADC_SC3_ADCO(0), //!< Normal operation i.e. a single conversion will be done when triggered.
   AdcContinuous_Enabled  = ADC_SC3_ADCO(1), //!< Continuous conversions enabled i.e. a continuous sequence of conversion will e triggered.
};

/**
 * Controls the ADC compare function
 */
enum AdcCompare {
   AdcCompare_Disabled              = ADC_SC2_ACFE(0),                                          //!< Comparisons disabled
   AdcCompare_LessThan              = ADC_SC2_ACFE(1)|ADC_SC2_ACFGT(0)|ADC_SC2_ACREN(0),        //!< ADC_value < low
   AdcCompare_GreaterThanOrEqual    = ADC_SC2_ACFE(1)|ADC_SC2_ACFGT(1)|ADC_SC2_ACREN(0),        //!< ADC_value >= low
   AdcCompare_OutsideRangeExclusive = (0<<8)|ADC_SC2_ACFE(1)|ADC_SC2_ACFGT(0)|ADC_SC2_ACREN(1), //!< (ADC_value < low) || (ADC_value > high)
   AdcCompare_OutsideRangeInclusive = (1<<8)|ADC_SC2_ACFE(1)|ADC_SC2_ACFGT(1)|ADC_SC2_ACREN(1), //!< (ADC_value <= low) || (ADC_value >= high)
   AdcCompare_InsideRangeExclusive  = (1<<8)|ADC_SC2_ACFE(1)|ADC_SC2_ACFGT(0)|ADC_SC2_ACREN(1), //!<  low < ADC_value < high
   AdcCompare_InsideRangeInclusive  = (0<<8)|ADC_SC2_ACFE(1)|ADC_SC2_ACFGT(1)|ADC_SC2_ACREN(1), //!<  low <= ADC_value <= high
};

/**
 * Type definition for ADC interrupt call back
 *
 * @param[in] value Conversion value from channel
 * @param[in] value Channel number for the conversion
 */
typedef void (*ADCCallbackFunction)(uint32_t value, int channel);

/**
 * Template class representing an ADC
 *
 * Example
 * @code
 *  // Instantiate ADC channel adc0_se8
 *  const AdcBase_T<adc0Info> Adc0;
 *
 *  // Initialise ADC
 *  Adc0.setMode(AdcResolution_16bit_se);
 *  @endcode
 *
 * @tparam info Table of information describing ADC
 */
template<class Info>
class AdcBase_T {

private:
   /**
    * This class is not intended to be instantiated
    */
   AdcBase_T() = delete;
   AdcBase_T(const AdcBase_T&) = delete;
   AdcBase_T(AdcBase_T&&) = delete;

protected:
   /** Clock register for peripheral */
   static constexpr volatile uint32_t *clockReg = Info::clockReg;

   /** Callback to catch unhandled interrupt */
   static void errorCallback(uint32_t, int) {
      setAndCheckErrorCode(E_NO_HANDLER);
   }
public:
   /** Peripheral hardware instance */
   static constexpr volatile ADC_Type *adc      = Info::adc;

   /**
    * Basic enable of ADC\n
    * Includes configuring all pins
    */
   static void enable() {
      // Configure pins
      Info::initPCRs();
      Info::InfoDP::initPCRs();
      Info::InfoDM::initPCRs();

      // Enable clock to ADC
      *clockReg  |= Info::clockMask;
      __DMB();
   }

   /**
    * Configure with settings from Configure.usbdmProject.\n
    * Includes configuring all pins
    */
   static void defaultConfigure() {
      enable();

      // Set mode to default
      adc->CFG1 = Info::cfg1;
      adc->CFG2 = Info::cfg2;
      adc->SC2  = Info::sc2;
      adc->CV1  = Info::cv1;
      adc->CV1  = Info::cv2;
      enableNvicInterrupts();
   }

   /**
    * Configure ADC
    *
    * @param[in] adcResolution   Resolution for converter e.g. AdcResolution_16bit_se
    * @param[in] adcClockSource  Clock source e.g. AdcClockSource_Asynch
    * @param[in] adcClockDivider Clock divider e.g. AdcClockDivider_4
    * @param[in] adcSample       Input sample interval. Allows use of higher input impedance sources
    * @param[in] adcPower        Allows reduced power consumption but with restricted input clock speed
    * @param[in] adcMuxsel       Selects between A/B multiplexor inputs on channels 4-8
    * @param[in] adcClockRange   Allows higher input clock speed operation
    * @param[in] adcAsyncClock   Controls whether the internal ADC clock is always enabled or only when needed for a conversion
    *
    * @note These settings apply to all channels on the ADC.\n
    * The resulting ADC clock rate should be restricted to the following ranges (assumes AdcPower_Normal, AdcClockRange_high):\n
    *  [2..12MHz] for 16-bit conversion modes  \n
    *  [1..18MHz] for other conversion modes
    */
   static void __attribute__((always_inline)) configure(
         AdcResolution   adcResolution,
         AdcClockSource  adcClockSource  = AdcClockSource_Asynch,
         AdcClockDivider adcClockDivider = AdcClockDivider_1,
         AdcSample       adcSample       = AdcSample_Normal,
         AdcPower        adcPower        = AdcPower_Normal,
         AdcMuxsel       adcMuxsel       = AdcMuxsel_B,
         AdcClockRange   adcClockRange   = AdcClockRange_high,
         AdcAsyncClock   adcAsyncClock   = AdcAsyncClock_disabled
         ) {
      enable();
      adc->CFG1 = adcResolution|adcClockSource|adcClockDivider|adcPower|(adcSample&ADC_CFG1_ADLSMP_MASK);
      adc->CFG2 = adcMuxsel|adcClockRange|adcAsyncClock|(adcSample&ADC_CFG2_ADLSTS_MASK);
   }

   /**
    * Enable/disable interrupts in NVIC
    *
    * @param[in] enable true to enable, false to disable
    */
   static __attribute__((always_inline)) void enableNvicInterrupts(bool enable=true) {

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
    * Disables the ADC\n
    * Does not change ADC pin mapping
    */
   static void disable() {
      adc->CFG1 = 0;
      adc->CFG2 = 0;
      adc->SC2  = 0;
   }

   /**
    * Set conversion mode
    *
    * @param[in] adcResolution Resolution for converter e.g. AdcResolution_16bit_se
    *
    * @note This affects all channels on the ADC
    */
   static __attribute__((always_inline)) void setResolution(AdcResolution adcResolution) {
      adc->CFG1 = (adc->CFG1&~ADC_CFG1_MODE_MASK)|adcResolution;
   }

   /**
    * Set clock source
    *
    * @param[in] adcClockSource  Clock source e.g. AdcClockSource_Asynch
    * @param[in] adcClockDivider Clock divider e.g. AdcClockDivider_4
    *
    * @note This affects all channels on the ADC.\n
    * The resulting ADC clock rate should be restricted to the following ranges:\n
    *  [2..12MHz] for 16-bit conversion modes  \n
    *  [1..18MHz] for other conversion modes
    */
   static __attribute__((always_inline)) void setClockSource(AdcClockSource adcClockSource, AdcClockDivider adcClockDivider=AdcClockDivider_1) {
      adc->CFG1 = (adc->CFG1&~(ADC_CFG1_ADIV_MASK|ADC_CFG1_ADICLK_MASK))|adcClockSource|adcClockDivider;
   }

   /**
    * Enable ADC internal asynchronous clock source
    *
    * @param[in] enable true to enable clock, false to disable
    *
    * @note It is not necessary to enable the internal clock to use it as an ADC clock source.\n
    *       If the internal clock is selected, it will be automatically enabled when an ADC conversion is initiated.\n
    *       However, enabling it beforehand will reduce the latency of the 1st conversion in a sequence.
    */
   static __attribute__((always_inline)) void enableAsynchronousClock(bool enable=true) {
      if (enable) {
         adc->CFG1 |= ADC_CFG2_ADACKEN_MASK;
      }
      else {
         adc->CFG1 &= ~ADC_CFG2_ADACKEN_MASK;
      }
   }

   /**
    * Set averaging mode
    *
    * @param[in] adcAveraging Mode for averaging e.g. AdcAveraging_4 etc
    *
    * @note This affects all channels on the ADC
    */
   static __attribute__((always_inline)) void setAveraging(AdcAveraging adcAveraging) {
      adc->SC3 = (adc->SC3&~(ADC_SC3_AVGE_MASK|ADC_SC3_AVGS_MASK))|adcAveraging;
   }

   /* ADC calibrate
    *
    * Calibrates the ADC
    *
    * @note Set up the ADC clock and resolution before calibration
    *
    * @return E_NO_ERROR       Calibration successful
    * @return E_CALIBRATE_FAIL Failed calibration
    */
   static ErrorCode calibrate() {

      // Save current SC3 as modified
      uint8_t sc3 = adc->SC3;

      // Start calibration
      setAveraging(AdcAveraging_Cal);

      // Wait for calibration to complete
      while (adc->SC3 & ADC_SC3_CAL_MASK) {
         __asm__("nop");
      }

      bool failed = adc->SC3 & ADC_SC3_CALF_MASK;

      // Restore original SC3 value
      adc->SC3 = sc3;

      // Check calibration outcome
      if(failed) {
         // Failed calibration
         return setErrorCode(E_CALIBRATE_FAIL);
      }

      // Calibration factor
      uint16_t calib;

      calib = adc->CLPS + adc->CLP4 + adc->CLP3 + adc->CLP2 + adc->CLP1 + adc->CLP0;
      calib /= 2;
      calib |= (1<<15);  // Set MSB
      adc->PG = calib;

      calib = 0;
      calib += adc->CLMS + adc->CLM4 + adc->CLM3 + adc->CLM2 + adc->CLM1 + adc->CLM0;
      calib /= 2;
      calib |= (1<<15);  // Set MSB
      adc->MG = calib;

      return E_NO_ERROR;
   }
   /**
    * Configure comparison mode
    *
    * @param[in] adcCompare   Comparison operation to enable
    * @param[in] low          Lower threshold
    * @param[in] high         Higher threshold (if needed)
    */
   static void enableComparison(AdcCompare adcCompare, int low=INT_MIN, int high=INT_MAX) {
#ifdef DEBUG_BUILD
      assert (low<=high);
#endif
      // Juggle CV1, CV2 values to satisfy comparison rules
      switch (adcCompare) {
         case AdcCompare_Disabled:
            break;
         case AdcCompare_LessThan:
         case AdcCompare_GreaterThanOrEqual:
            adc->CV1 = low;
            break;
         case AdcCompare_OutsideRangeExclusive:
         case AdcCompare_InsideRangeInclusive:
            adc->CV1 = low;
            adc->CV2 = high;
            break;
         case AdcCompare_InsideRangeExclusive:
         case AdcCompare_OutsideRangeInclusive:
            adc->CV1 = high;
            adc->CV2 = low;
            break;
      }
      // Set comparison fields
      adc->SC2 |= (adc->SC2&~(ADC_SC2_ACFE(1)|ADC_SC2_ACFGT(1)|ADC_SC2_ACREN(1)))|
            (adcCompare&(ADC_SC2_ACFE(1)|ADC_SC2_ACFGT(1)|ADC_SC2_ACREN(1)));
   }

protected:
   /**
    * Enables hardware trigger mode of operation and configures the channel
    *
    * @param[in] sc1Value        SC1 register value including the ADC channel, Differential mode and interrupt enable
    * @param[in] adcPretrigger   Hardware pre-trigger to use for this channel\n
    *                            This corresponds to pre-triggers in the PDB channels and SC1[n] register setups
    * @param[in] adcDma          Whether to generate a DMA request when each conversion completes
    */
   static void enableHardwareConversion(int sc1Value, AdcPretrigger adcPretrigger, AdcDma adcDma) {
      // Set hardware triggers
      adc->SC2 = (adc->SC2)|ADC_SC2_ADTRG(1)|adcDma;
      // Configure channel for hardware trigger input
      adc->SC1[adcPretrigger] = sc1Value;
   }

   /**
    * Initiates a conversion but does not wait for it to complete.
    *
    * @param[in] sc1Value       SC1 register value. This includes channel, differential mode and interrupts enable.
    * @param[in] adcContinuous  Select continuous conversion mode
    *
    * @return E_NO_ERROR on success
    */
   static __attribute__((always_inline)) ErrorCode startConversion(const int sc1Value, AdcContinuous adcContinuous) {

      if ((sc1Value&&ADC_SC1_AIEN_MASK) && !Info::irqHandlerInstalled) {
         // Enabling interrupts without a handler installed in vector table
         return setErrorCode(E_NO_HANDLER);
      }
      if (adcContinuous) {
         adc->SC3 |= ADC_SC3_ADCO_MASK;
      }
      else {
         adc->SC3 &= ~ADC_SC3_ADCO_MASK;
      }
      // Trigger conversion
      adc->SC1[0] = sc1Value;

      return E_NO_ERROR;
   };

   /**
    * Initiates a conversion and waits for it to complete
    *
    * @param[in] sc1Value SC1 register value including the ADC channel to use
    *
    * @return - the result of the conversion (should be treated as signed if differential channel)
    */
   static uint16_t readAnalogue(const int sc1Value) {

      // Trigger conversion
      adc->SC1[0] = (sc1Value&(ADC_SC1_ADCH_MASK|ADC_SC1_AIEN_MASK|ADC_SC1_DIFF_MASK));

      while ((adc->SC1[0]&ADC_SC1_COCO_MASK) == 0) {
         __asm__("nop");
      }
      return (uint16_t)adc->R[0];
   };

};

/**
 * Template class to provide ADC callback
 */
template<class Info>
class AdcIrq_T : public AdcBase_T<Info> {

protected:
   /** Callback function for ISR */
   static ADCCallbackFunction callback;

public:

   using AdcInfo = Info;

   /**
    * IRQ handler
    */
   static void irqHandler() {
      if (AdcBase_T<Info>::adc->SC1[0] & ADC_SC1_COCO_MASK) {
         callback(AdcBase_T<Info>::adc->R[0], AdcBase_T<Info>::adc->SC1[0]&ADC_SC1_ADCH_MASK);
      }
      if (AdcBase_T<Info>::adc->SC1[1] & ADC_SC1_COCO_MASK) {
         callback(AdcBase_T<Info>::adc->R[1], AdcBase_T<Info>::adc->SC1[1]&ADC_SC1_ADCH_MASK);
      }
   }

   /**
    * Set Callback function
    *
    * @param[in] theCallback Callback function to execute on interrupt.\n
    *            nullptr to remove handler
    */
   static void setCallback(ADCCallbackFunction theCallback) {
      if (theCallback == nullptr) {
         callback = AdcBase_T<Info>::errorCallback;
         return;
      }
      callback = theCallback;
   }
};

template<class Info> ADCCallbackFunction AdcIrq_T<Info>::callback = AdcBase_T<Info>::errorCallback;

/**
 * Template class representing an ADC channel
 *
 * Example
 * @code
 * // Instantiate the ADC channel (for ADC0 channel 6)
 * using Adc0_ch6 = USBDM::AdcChannel_T<Adc0Info, 6>;
 *
 * // Set ADC resolution
 * Adc0_ch6.setMode(AdcResolution_16bit_se);
 *
 * // Read ADC value
 * uint32_t value = Adc0_ch6.readAnalogue();
 * @endcode
 *
 * @tparam info    Table of information describing ADC
 * @tparam channel ADC channel
 */
template<class Info, int channel>
class AdcChannel_T : public AdcBase_T<Info>, CheckSignal<Info, channel> {

public:
   /** Allow convenient access to owning ADC */
   using Adc =  AdcBase_T<Info>;

   /** Channel number */
   static constexpr int CHANNEL=channel;

   /**
    * Enables hardware trigger mode of operation and configures a channel
    *
    * @param[in] adcPretrigger   Hardware pre-trigger to use for this channel\n
    *                            This corresponds to pre-triggers in the PDB channels and SC1[n]/R[n] register selection
    * @param[in] enableInterrupt Whether to generate an interrupt when each conversion completes
    * @param[in] adcDma          Whether to generate a DMA request when each conversion completes
    */
   static void enableHardwareConversion(AdcPretrigger adcPretrigger, AdcInterrupt enableInterrupt=AdcInterrupt_disable, AdcDma adcDma=AdcDma_Disable) {
      AdcBase_T<Info>::enableHardwareConversion(channel|enableInterrupt, adcPretrigger, adcDma);
   }

   /**
    * Initiates a conversion but does not wait for it to complete.
    *
    * @param[in] adcInterrupt   Determines if an interrupt is generated when conversions are complete
    * @param[in] adcContinuous  Select continuous conversion mode
    */
   static __attribute__((always_inline)) void startConversion(AdcInterrupt adcInterrupt=AdcInterrupt_disable, AdcContinuous adcContinuous=AdcContinuous_Disabled) {
      AdcBase_T<Info>::startConversion(channel|adcInterrupt, adcContinuous);
   };

   /**
    * Initiates a conversion and waits for it to complete
    *
    * @return - the result of the conversion
    */
   static __attribute__((always_inline)) uint32_t readAnalogue() {
      // Zero extended to 32 bits
      return (uint32_t)(uint16_t)AdcBase_T<Info>::readAnalogue(channel);
   };
};

/**
 * Template class representing an ADC differential channel
 *
 * Example
 * @code
 * // Instantiate the differential ADC channels (for ADC_DM0, ADC_DP0)
 * using Adc0 = USBDM::Adc0DiffChannel<Adc0Info,0>;
 *
 * // Set ADC resolution
 * Adc0.setMode(AdcResolution_11bit_diff );
 *
 * // Read ADC value
 * uint32_t value = Adc0.readAnalogue();
 * @endcode
 *
 * @tparam info    Table of information describing ADC
 * @tparam channel ADC channel
 */
template<class Info, int channel>
class AdcDiffChannel_T : public AdcBase_T<Info>, CheckSignal<typename Info::InfoDP, channel>, CheckSignal<typename Info::InfoDM, channel> {

public:
   /** Allow convenient access to owning ADC */
   using Adc =  AdcBase_T<Info>;

   /** Channel number */
   static constexpr int CHANNEL=channel;

   /**
    * Enables hardware trigger mode of operation and configures a channel
    *
    * @param[in] adcPretrigger   Hardware pre-trigger to use for this channel\n
    *                            This corresponds to pre-triggers in the PDB channels and SC1[n] register setups
    * @param[in] adcInterrupt    Whether to generate interrupt when complete
    * @param[in] adcDma          Whether to generate a DMA request when each conversion completes
    */
   static void enableHardwareConversion(AdcPretrigger adcPretrigger, AdcInterrupt adcInterrupt=AdcInterrupt_disable, AdcDma adcDma=AdcDma_Disable) {
      AdcBase_T<Info>::enableHardwareConversion(channel|ADC_SC1_DIFF_MASK|adcInterrupt, adcPretrigger, adcDma);
   }

   /**
    * Initiates a conversion but does not wait for it to complete.\n
    * Intended for use with interrupts so ADC interrupts are enabled
    *
    * @param[in] adcInterrupt   Determines if an interrupt is generated when conversions are complete
    * @param[in] adcContinuous  Select continuous conversion mode
    */
   static __attribute__((always_inline)) void startConversion(AdcInterrupt adcInterrupt=AdcInterrupt_disable, AdcContinuous adcContinuous=AdcContinuous_Disabled) {
      AdcBase_T<Info>::startConversion(channel|ADC_SC1_DIFF_MASK|adcInterrupt, adcContinuous);
   };
   /**
    * Initiates a conversion and waits for it to complete
    *
    * @return - the result of the conversion
    */
   static __attribute__((always_inline)) int32_t readAnalogue() {
      // Sign-extended to 32 bits
      return (int32_t)(int16_t)AdcBase_T<Info>::readAnalogue(channel|ADC_SC1_DIFF_MASK);
   };
};

#ifdef USBDM_ADC0_IS_DEFINED
/**
 * Template class representing an ADC0 channel
 *
 * Example
 * @code
 * // Instantiate the ADC channel (for ADC0 channel 6)
 * using Adc = USBDM::Adc0Channel<6>;
 *
 * // Set ADC resolution
 * Adc.setMode(AdcResolution_16bit_se);
 *
 * // Read ADC value
 * uint32_t value = Adc.readAnalogue();
 * @endcode
 *
 * @tparam channel ADC channel
 */
template<int channel>
class Adc0Channel : public AdcChannel_T<Adc0Info, channel> {
};
//template<int channel> using Adc0Channel = AdcChannel_T<Adc0Info, channel>;

/**
 * Template class representing an ADC0 differential channel
 *
 * Example
 * @code
 * // Instantiate the differential ADC0 channels (for ADC0_DM0, ADC0_DP0)
 * using Adc = USBDM::Adc0DiffChannel<0>;
 *
 * // Set ADC resolution
 * Adc.setMode(AdcResolution_11bit_diff );
 *
 * // Read ADC value
 * uint32_t value = Adc0.readAnalogue();
 * @endcode
 *
 * @tparam channel ADC channel
 */
template<int channel>
class Adc0DiffChannel : public AdcDiffChannel_T<Adc0Info, channel> {
};
//template<int channel> using Adc0DiffChannel = AdcDiffChannel_T<Adc0Info, channel>;

/**
 * Class representing ADC0
 */
using Adc0 = AdcIrq_T<Adc0Info>;
#endif

#ifdef USBDM_ADC1_IS_DEFINED
/**
 * Template class representing an ADC1 channel
 *
 * Example
 * @code
 * // Instantiate the ADC channel (for ADC1 channel 6)
 * using Adc = USBDM::Adc1Channel<6>;
 *
 * // Set ADC resolution
 * Adc.setMode(AdcResolution_16bit_se);
 *
 * // Read ADC value
 * uint32_t value = Adc.readAnalogue();
 * @endcode
 *
 * @tparam channel ADC channel
 */
template<int channel>
class Adc1Channel : public AdcChannel_T<Adc1Info, channel> {
};
//template<int channel> using Adc1Channel = AdcChannel_T<Adc1Info, channel>;

/**
 * Template class representing an ADC1 differential channel
 *
 * Example
 * @code
 * // Instantiate the differential ADC1 channels (for ADC1_DM0, ADC1_DP0)
 * using Adc = USBDM::Adc1DiffChannel<0>;
 *
 * // Set ADC resolution
 * Adc.setMode(AdcResolution_11bit_diff );
 *
 * // Read ADC value
 * uint32_t value = Adc.readAnalogue();
 * @endcode
 *
 * @tparam channel ADC channel
 */
template<int channel>
class Adc1DiffChannel : public AdcDiffChannel_T<Adc1Info, channel> {
};
//template<int channel> using Adc1DiffChannel = AdcDiffChannel_T<Adc01Info, channel>;

/**
 * Class representing ADC1
 */
using Adc1 = AdcIrq_T<Adc1Info>;
#endif

/**
 * @}
 */

} // End namespace USBDM

#endif /* HEADER_ADC_H */

