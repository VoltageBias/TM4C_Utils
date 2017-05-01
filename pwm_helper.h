////////////////////////////////////////////////////////////////////////////////
//
// VoltageBias - the Blog.
// Author: Gilbert Waltoon
//
// Released under a GNU General Public License v3.0
//
// FILENAME : pwm_helper.c
// PURPOSE  : A set of helper functions to operate the TM4C123 PWM module
//
// Version 0: Oct 30, 2016
//
////////////////////////////////////////////////////////////////////////////////

#ifndef TM4C_UTILS_PWM_HELPER_H_
#define TM4C_UTILS_PWM_HELPER_H_

#include "TM4C123GH6PM.h"
#include "tm4c_register_fields.h"


////////////////////////////////////////////////////////////////////////////////
//                PWM Helper function prototypes follow                       //
////////////////////////////////////////////////////////////////////////////////

// Call to run an example. Writes to the UART@115200Baud
void fPWMExample();

////////////////////////////////////////////////////////////////////////////////
// fstartPWM()...
//
// For a Desired PWM Frequency and Duty [0..1] pass in:
//
// ui32_PWM0LOAD = ( SYS_CLOCK_HZ / 2xDesired-frequency ) - 1
// ui32_PWM0CMPA = ((1 - Desired-duty-PWM_A) x (SYS_CLOCK_HZ / 2xDesired-freq.))-1
// ui32_PWM0CMPA = ((1 - Desired-duty-PWM_B) x (SYS_CLOCK_HZ / 2xDesired-freq.))-1
//
// For example, for desired 25kHz, PWMa= 0.25, PWMb = 0.75 duty, SYS_CLOCK_HZ=16MHz
//   ui32_PWM0LOAD = 16,000,000/(2x25,000) - 1 =  319
//   ui32_PWM0CMPA = ( (1-0.25) x 320 ) - 1 = 239
//   ui32_PWM0CMPB = ( (1-0.75) x 320 ) - 1 = 79

void fStartPWM(uint32_t ui32_PWM0LOAD,        \
               uint32_t ui32_PWM0CMPA,        \
               uint32_t ui32_PWM0CMPB );

////////////////////////////////////////////////////////////////////////////////


/* todo Approach of supplying a constructor at compile time not yet implemnted
////////////////////////////////////////////////////////////////////////////////
//                Definitions of PWMCfg structures follows                      //
////////////////////////////////////////////////////////////////////////////////
//

// When intialising one of the 2xADC's we need to know which board-pins/ports
// that ADC uses. We pass this information inside an AINx structure.
//
// For a detailed explanation of the approach to creating structures at compile
// time, see VoltageBias - the Blog - 29 Oct 2016.
//
// The struct. derives from the ADC init. procedure p.817 TM4C123GH6PM d'sheet
//
// struct {
//  uint32_t RCGCGPIO_Rx;   "Enable clk to appropriate GPIO via RCGCGPIO reg."
//  GPIOA_Type *GPIOx;      The port used  by the GPIO
//  uint32_t GPIODIR_DIR_x; Set pin as input
//  uint32_t GPIOAFSEL_AFSEL_x; "Set GPIO AFSEL bits for the appropriate pins
//  uint32_t GPIODEN_DEN_x; "Config AINx sigs to be analog ip's by clearing DEN
//  uint32_t GPIOAMSEL_GPIOAMSEL_x; "Disable the analog isolation circuit"
//        }
//
typedef struct {
                    uint32_t RCGCGPIO_Rx;            \
                    GPIOA_Type *GPIOx;               \
                    uint32_t GPIODIR_DIR_x;          \
                    uint32_t GPIOAFSEL_AFSEL_x;      \
                    uint32_t GPIODEN_DEN_x;          \
                    uint32_t GPIOAMSEL_GPIOAMSEL_x;  \
                } PWMcfg_t, *pPWMcfg_t;


// Declare the constructor function that assembles a
// PWM configuration  at compile time
pPWMcfg_t fConstructPWMcfg(                          \
                        uint32_t,                     \
                        GPIOA_Type*,                  \
                        uint32_t,                     \
                        uint32_t,                     \
                        uint32_t,                     \
                        uint32_t                      \
                         );
*/
// // Configuare the sample sequence for the ADC defined within the SS_CFG structure
// void fStartPWM(PWMcfg_t*);

#endif /* TM4C_UTILS_PWM_HELPER_H_ */
