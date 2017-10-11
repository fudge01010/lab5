/**
 * @file     usbdmError.cpp (180.ARM_Peripherals/Sources/usbdmError.cpp)
 * @brief    Error handling
 *
 * @version  V4.12.1.80
 * @date     13 April 2016
 */
#include <stdio.h>
#include "hardware.h"

namespace USBDM {

/** Last error set by USBDM code */
volatile ErrorCode errorCode = E_NO_ERROR;

/** Table of error messages indexed by error code */
static const char *messages[] = {
      "No error",
      "General error",
      "Too small",
      "Too large",
      "Illegal parameter",
      "Interrupt handler not installed",
      "Flash initialisation failed",
      "ADC Calibration failed",
};

/**
 * Get USBDM error code
 *
 * @return  err Error code
 */
ErrorCode getError() {
   return errorCode;
}

/**
 * Get error message from error code or last error if not provided
 *
 * @param  err Error code
 *
 * @return Pointer to static string
 */
const char *getErrorMessage(ErrorCode err) {
#ifdef __CMSIS_RTOS
   // Check for CMSIS error codes
   if (err & E_CMSIS_ERR_OFFSET) {
      return "CMSIS error";
   }
#endif
   if (err>(sizeof(messages)/sizeof(messages[0]))) {
      return "Unknown error";
   }
   return messages[err];
}

#ifdef DEBUG_BUILD
/**
 * Check for error code being set (drastically!)
 * This routine does not return if there is an error
 */
ErrorCode checkError() {
   while (errorCode != E_NO_ERROR) {
      const char *msg = getErrorMessage();
      __attribute__((unused))
      int cmsisErrorCode = errorCode & ~E_CMSIS_ERR_OFFSET;
      puts(msg);
      // If you arrive here then an error has been detected.
      // If a CMSIS error, check the 'cmsisErrorCode' above and refer to the CMSIS error codes
      __BKPT();
   }
   return errorCode;
}
#endif

} // end namespace USBDM
