/*
 * tsi.h (180.ARM_Peripherals/Project_Headers/tsi-MK.h)
 *
 *  Created on: 25/10/2013
 *      Author: podonoghue
 */

#ifndef TSI_H_
#define TSI_H_
 /*
 * *****************************
 * *** DO NOT EDIT THIS FILE ***
 * *****************************
 *
 * This file is generated automatically.
 * Any manual changes will be lost.
 */
#include "hardware.h"

namespace USBDM {

/**
 * Active mode clock source
 */
enum TsiClockSource {
   TsiClockSource_LpOscClk = TSI_SCANC_AMCLKS(0), // Low Power Oscillator (PMC 1kHz oscillator)
   TsiClockSource_McgIrClk = TSI_SCANC_AMCLKS(1), // MCG IR Clock
   TsiClockSource_OscerClk = TSI_SCANC_AMCLKS(2), // Oscillator external reference clock
};
/**
 * Active mode clock divider
 */
enum TsiClockDivider {
   TsiClockDivider_1     = TSI_SCANC_AMPSC(0), // Divide by 1
   TsiClockDivider_2     = TSI_SCANC_AMPSC(1), // Divide by 2
   TsiClockDivider_4     = TSI_SCANC_AMPSC(2), // Divide by 4
   TsiClockDivider_8     = TSI_SCANC_AMPSC(3), // Divide by 8
   TsiClockDivider_16    = TSI_SCANC_AMPSC(4), // Divide by 16
   TsiClockDivider_32    = TSI_SCANC_AMPSC(5), // Divide by 32
   TsiClockDivider_64    = TSI_SCANC_AMPSC(6), // Divide by 64
   TsiClockDivider_128   = TSI_SCANC_AMPSC(7), // Divide by 1128
};
/**
 * Low Power Mode clock source (LLS, VLLSx)
 */
enum TsiLowPowerClockSource {
   TsiLowPowerClockSource_LpOscClk   = TSI_GENCS_LPCLKS(0), // Low Power Oscillator (PMC 1kHz oscillator)
   TsiLowPowerClockSource_ERClk32k   = TSI_GENCS_LPCLKS(1), // External 32K Oscillator (RTC or main oscillator in 32K mode)
};
/**
 * Low Power Mode scan interval (LLS, VLLSx)
 */
enum TsiLowPowerScanInterval {
   TsiLowPowerScanInterval_1ms     = TSI_GENCS_LPSCNITV(0),  // 1ms   scan interval
   TsiLowPowerScanInterval_5ms     = TSI_GENCS_LPSCNITV(1),  // 5ms   scan interval
   TsiLowPowerScanInterval_10ms    = TSI_GENCS_LPSCNITV(2),  // 10ms  scan interval
   TsiLowPowerScanInterval_15ms    = TSI_GENCS_LPSCNITV(3),  // 15ms  scan interval
   TsiLowPowerScanInterval_20ms    = TSI_GENCS_LPSCNITV(4),  // 20ms  scan interval
   TsiLowPowerScanInterval_30ms    = TSI_GENCS_LPSCNITV(5),  // 30ms  scan interval
   TsiLowPowerScanInterval_40ms    = TSI_GENCS_LPSCNITV(6),  // 40ms  scan interval
   TsiLowPowerScanInterval_50ms    = TSI_GENCS_LPSCNITV(7),  // 50ms  scan interval
   TsiLowPowerScanInterval_75ms    = TSI_GENCS_LPSCNITV(8),  // 75ms  scan interval
   TsiLowPowerScanInterval_100ms   = TSI_GENCS_LPSCNITV(9),  // 100ms scan interval
   TsiLowPowerScanInterval_125ms   = TSI_GENCS_LPSCNITV(10), // 125ms scan interval
   TsiLowPowerScanInterval_150ms   = TSI_GENCS_LPSCNITV(11), // 150ms scan interval
   TsiLowPowerScanInterval_200ms   = TSI_GENCS_LPSCNITV(12), // 200ms scan interval
   TsiLowPowerScanInterval_300ms   = TSI_GENCS_LPSCNITV(13), // 300ms scan interval
   TsiLowPowerScanInterval_400ms   = TSI_GENCS_LPSCNITV(14), // 400ms scan interval
   TsiLowPowerScanInterval_500ms   = TSI_GENCS_LPSCNITV(15), // 500ms scan interval
};
/**
 * Electrode oscillator prescaler
 */
enum TsiElectrodePrescaler {
   TsiElectrodePrescaler_1     = TSI_GENCS_PS(0), // Divide by 1
   TsiElectrodePrescaler_2     = TSI_GENCS_PS(1), // Divide by 2
   TsiElectrodePrescaler_4     = TSI_GENCS_PS(2), // Divide by 4
   TsiElectrodePrescaler_8     = TSI_GENCS_PS(3), // Divide by 8
   TsiElectrodePrescaler_16    = TSI_GENCS_PS(4), // Divide by 16
   TsiElectrodePrescaler_32    = TSI_GENCS_PS(5), // Divide by 32
   TsiElectrodePrescaler_64    = TSI_GENCS_PS(6), // Divide by 64
   TsiElectrodePrescaler_128   = TSI_GENCS_PS(7), // Divide by 1128
};

/**
 * Selects if a single software scan is initiated or period scans
 */
enum TsiScanMode {
   TsiScanMode_Disabled     = TSI_GENCS_TSIEN(0)|TSI_GENCS_STM(0)|TSI_GENCS_SWTS(0), // Module disabled
   TsiScanMode_Triggered    = TSI_GENCS_TSIEN(1)|TSI_GENCS_STM(0)|TSI_GENCS_SWTS(1), // Enable & software triggered single scan
   TsiScanMode_Periodic     = TSI_GENCS_TSIEN(1)|TSI_GENCS_STM(1)|TSI_GENCS_SWTS(0), // Enable hardware scanning (repeated periodically)
};

/**
 * Selects if the module operates in selected low power modes
 */
enum TsiStopMode {
   TsiStopMode_Disabled    = TSI_GENCS_STPE(0), // Disabled in Stop, VLPStop, LLS, VLLSx
   TsiStopMode_Enabled     = TSI_GENCS_STPE(1), // Enabled in Stop, VLPStop, LLS, VLLSx
};

enum TsiInterrupt {
   TsiInterrupt_Disable    = TSI_GENCS_TSIIE(0)|TSI_GENCS_ESOR(0),   // Interrupts disabled
   TsiInterrupt_OutOfRange = TSI_GENCS_TSIIE(1)|TSI_GENCS_ESOR(0),   // Interrupt generated on Out-of-Range condition (OUTRGF flag)
   TsiInterrupt_EndOfScan  = TSI_GENCS_TSIIE(1)|TSI_GENCS_ESOR(1),   // Interrupt generated on End-of-Scan condition (EOSF flag)
};
enum TsiErrorInterrupt {
   TsiErrorInterrupt_Disable  = TSI_GENCS_ERIE(0),   // Error interrupts disabled
   TsiErrorInterrupt_Enable   = TSI_GENCS_ERIE(1),   // Error interrupts enabled (overrun or illegal measurement result)
};
/**
 * Type definition for TSI interrupt call back
 *
 *  @param[in]  status - Interrupt flags e.g. TSI_GENCS_EOSF_MASK, TSI_GENCS_OVRF_MASK, TSI_GENCS_EXTERF_MASK
 */
typedef void (*TSICallbackFunction)(uint32_t status);

/**
 * Interface for Touch Sense Module (TSI)
 *
 * Notes:
 *  The TSI operates in active mode for MCU in Run, Wait, Stop, VLPRun, VLPWait and VLPStop.
 *  The TSI operates on low-power mode for MCU in low-leakage modes LLS, VLLSx.
 *  Only a single electrode is scanned (PEN.LPSP) for low-power mode.
 */
template <class Info>
class TsiBase_T {

protected:
   static constexpr volatile TSI_Type *tsi      = Info::tsi;
   static constexpr volatile uint32_t *clockReg = Info::clockReg;

   static void unhandledInterrupt(uint32_t) {
      setAndCheckErrorCode(E_NO_HANDLER);
   }
public:
   /**
    * Enables TSI bus interface clock and configures all pins
    */
   static void enable() {
      *clockReg |= Info::clockMask;
      __DMB();

      Info::initPCRs();
   }

   /**
    * Initialise TSI to default settings determined by Configure.usbdmProject\n
    * Configures all TSI pins.
    */
   static void defaultConfigure() {
      enable();

      tsi->GENCS     = Info::tsi_gencs|TSI_GENCS_TSIEN_MASK;
      tsi->SCANC     = Info::tsi_scanc;
      tsi->THRESHOLD = Info::tsi_threshold;
      tsi->PEN       = Info::tsi_pen;

      enableNvicInterrupts();
   }

   /**
    * Enable/disable interrupts in NVIC
    *
    * @param[in]  enable True => enable, False => disable
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
    * Set the electrode scan configuration for active mode.\n
    * This controls the count interval of the internal oscillator when sampling a pin:\n
    *   T = (Prescaler*consecutiveScans)/Felectrode\n
    * The reference oscillator is counted for the above interval to get the electrode measurement.
    *
    * tsiElectrodePrescaler Electrode oscillator prescaler.
    * consecutiveScans      The number of consecutive scans of an electrode
    */
   static void setScans(TsiElectrodePrescaler tsiElectrodePrescaler, int consecutiveScans) {

      tsi->GENCS = (tsi->GENCS&~(TSI_GENCS_PS_MASK|TSI_GENCS_NSCN_MASK))|tsiElectrodePrescaler|TSI_GENCS_NSCN(consecutiveScans-1);
   }
   /**
    * Set clock source, clock divider and modulus for active mode
    *
    * @param[in] tsiClockSource  Clock source
    * @param[in] tsiClockDivider Clock divider
    * @param[in] scanModulus     Scan modulus (0=continuous, otherwise scan period)
    */
   static void setClock(
         TsiClockSource  tsiClockSource   = TsiClockSource_LpOscClk,
         TsiClockDivider tsiClockDivider  = TsiClockDivider_128,
         uint16_t        scanModulus      = 0 ) {

      tsi->SCANC = (tsi->SCANC&~(TSI_SCANC_AMCLKS_MASK|TSI_SCANC_AMPSC_MASK|TSI_SCANC_SMOD_MASK))|
            TSI_SCANC_SMOD(scanModulus)|tsiClockSource|tsiClockDivider;
   }
   /**
    * Sets how often the inputs are scanned.
    *
    * @param[in] period The period of scanning.
    *
    * @note This period must be larger than the total measurement time as determined by other parameters e.g.
    *  - Electrode oscillation period (electrode/finger capacitance, electrode current)
    *  - Electrode oscillator divider and consecutive scans settings
    *  - Number of electrodes scanned.
    */
   static ErrorCode setSamplePeriod(float period) {
      float inputClock = Info::getInputClockFrequency();
      int prescaleFactor=1;
      int prescalerValue=0;

      // Maximum period value in ticks
      uint32_t maxPeriodInTicks = 255;

      while (prescalerValue<=7) {
         float    clock = inputClock/prescaleFactor;
         uint32_t periodInTicks = round(period*clock);
         if (periodInTicks <= maxPeriodInTicks) {
            tsi->SCANC = (tsi->SCANC&~(TSI_SCANC_AMPSC_MASK|TSI_SCANC_SMOD_MASK))|
                  TSI_SCANC_AMPSC(prescalerValue)|TSI_SCANC_SMOD(periodInTicks);
            return E_NO_ERROR;
         }
         prescalerValue++;
         prescaleFactor <<= 1;
      }
      // Too long a period
      return setErrorCode(E_TOO_LARGE);
   }
   /**
    * Set mode, clock source and scan interval for low power mode
    *
    * @param[in] tsiStopMode             Selects if the module operates in low power modes
    * @param[in] tsiLowPowerScanInterval Scan interval in low power modes
    * @param[in] tsiLowPowerClockSource  Clock source in low power modes
    */
   static void setLowPowerClock(
         TsiStopMode             tsiStopMode,
         TsiLowPowerScanInterval tsiLowPowerScanInterval = TsiLowPowerScanInterval_500ms,
         TsiLowPowerClockSource  tsiLowPowerClockSource  = TsiLowPowerClockSource_LpOscClk) {

      tsi->GENCS = (tsi->GENCS&~(TSI_GENCS_STPE_MASK|TSI_GENCS_LPCLKS_MASK|TSI_GENCS_LPSCNITV_MASK))|
            tsiStopMode|tsiLowPowerScanInterval|tsiLowPowerClockSource;
   }
   /**
    * Set reference and external charge currents
    *
    * @param[in] referenceCharge Reference charge current (uA in 2uA steps)
    * @param[in] externalCharge  External oscillator charge current (uA in 2uA steps)
    */
   static void setCurrents(uint16_t referenceCharge=16, uint16_t externalCharge=16) {

      tsi->SCANC = (tsi->SCANC&~(TSI_SCANC_REFCHRG_MASK|TSI_SCANC_EXTCHRG_MASK))|
            TSI_SCANC_REFCHRG((referenceCharge+1)/2)|TSI_SCANC_EXTCHRG((externalCharge+1)/2);
   }
   /**
    * Select inputs to be scanned
    *
    * @param[in] activeChannels  Bit-mask for channels in use in active mode
    * @param[in] lowpowerChannel Channel used in low-power mode
    */
   static void selectInputs(uint16_t activeChannels, int lowpowerChannel) {

      TSI0->PEN = TSI_PEN_PEN(activeChannels)|TSI_PEN_LPSP(lowpowerChannel);
   }
   /**
    * Set low-power channel thresholds
    *
    * @param[in] low  Low threshold
    * @param[in] high High threshold
    */
   static void setLowPowerThresholds(uint16_t low, int high) {

      TSI0->THRESHOLD = TSI_THRESHOLD_HTHH(high)|TSI_THRESHOLD_LTHH(low);
   }
   /**
    * Configure touch sensing interrupts
    *
    * @param[in] tsiInterrupt       Selects End-of-Scan or Out-of-Range interrupt behaviour
    * @param[in] tsiErrorInterrupt  Selects error interrupt behaviour
    */
   static void enableTsiInterrupts(
         TsiInterrupt      tsiInterrupt,
         TsiErrorInterrupt tsiErrorInterrupt = TsiErrorInterrupt_Disable) {
      tsi->GENCS = (tsi->GENCS&~(TSI_GENCS_TSIIE_MASK|TSI_GENCS_ERIE_MASK))|tsiInterrupt|tsiErrorInterrupt;
   }

   /**
    * Get channel count value
    *
    * @param[in]  channel Channel number
    *
    * @return 16-bit count value
    */
   static uint16_t getCount(int channel) {
      return Info::tsi->CNTR[channel];
   }

   /**
    * Enable TSI and start scan
    *
    * @param tsiScanMode Controls if a single software scan is initiated or periodic scans
    */
   static void startScan(TsiScanMode tsiScanMode) {
      // Disable module so changes have effect
      // This also helps with errata e4181
      tsi->GENCS &= ~TSI_GENCS_TSIEN_MASK|TSI_GENCS_SWTS_MASK;

      // Select Hardware/Software mode
      tsi->GENCS |= (tsiScanMode&TSI_GENCS_STM_MASK);

      // Enable
      tsi->GENCS |= TSI_GENCS_TSIEN_MASK;

      // Clear flags and start scan
      tsi->GENCS |=
            tsiScanMode|            // Software/Hardware mode + optional software trigger
            TSI_GENCS_EOSF_MASK|    // Clear flags
            TSI_GENCS_OUTRGF_MASK|
            TSI_GENCS_EXTERF_MASK|
            TSI_GENCS_OVRF_MASK;
   }

   /**
    * Start software scan and wait for completion\n
    *
    * @note This routine will hang if interrupts are used as the flags will be automatically
    *       cleared by the stub ISR
    */
   static ErrorCode startScanAndWait() {
      // Clear flags and start scan
      startScan(TsiScanMode_Triggered);

      // Wait for complete flag or error
      while ((tsi->GENCS&(TSI_GENCS_EOSF_MASK|TSI_GENCS_OUTRGF_MASK|TSI_GENCS_EXTERF_MASK|TSI_GENCS_OVRF_MASK)) == 0) {
      }

      return (tsi->GENCS&(TSI_GENCS_OUTRGF_MASK|TSI_GENCS_EXTERF_MASK|TSI_GENCS_OVRF_MASK))?E_ERROR:E_NO_ERROR;
   }
};

/**
 * Template class to provide TSI callback
 */
template<class Info>
class TsiIrq_T : public TsiBase_T<Info> {

protected:
   /** Callback function for ISR */
   static TSICallbackFunction callback;

public:
   /**
    * IRQ handler
    */
   static void irqHandler(void) {

      // Capture flags
      uint32_t status = TsiBase_T<Info>::tsi->GENCS;

      status &= TSI_GENCS_SCNIP_MASK|TSI_GENCS_EOSF_MASK|TSI_GENCS_OUTRGF_MASK|TSI_GENCS_OVRF_MASK|TSI_GENCS_EXTERF_MASK;

      if ((status&(TSI_GENCS_EOSF_MASK|TSI_GENCS_OUTRGF_MASK|TSI_GENCS_OVRF_MASK|TSI_GENCS_EXTERF_MASK)) == 0) {
         // Ignore spurious interrupts?
         return;
      }
      // Clear flags
      TsiBase_T<Info>::tsi->GENCS |= status; // w1c found flags
      if (status == (TSI_GENCS_SCNIP_MASK|TSI_GENCS_EOSF_MASK)) {
         // Ignore EOSF unless SCNIP is clear to avoid multiple events due to errata e3926
         // This assumes that there is at least some idle time between sequences - as there should be
         return;
      }
      // Execute call-back
      callback(status);
   }

   /**
    * Set Callback function
    *
    *   @param[in]  theCallback - Callback function to be executed on TSI alarm interrupt
    */
   static void setCallback(TSICallbackFunction theCallback) {
      if (theCallback == nullptr) {
         callback = TsiBase_T<Info>::unhandledInterrupt;
         return;
      }
      callback = theCallback;
   }
};

template<class Info> TSICallbackFunction TsiIrq_T<Info>::callback = TsiBase_T<Info>::unhandledInterrupt;

#ifdef USBDM_TSI_IS_DEFINED
/**
 * Class representing TSI
 */
using Tsi = TsiIrq_T<TsiInfo>;

#endif

#ifdef USBDM_TSI0_IS_DEFINED
/**
 * Class representing TSI
 */
using Tsi0 = TsiIrq_T<Tsi0Info>;

#endif

} // End namespace USBDM

#endif /* TSI_H_ */