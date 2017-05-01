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
					uint32_t RCGCGPIO_Rx; 			 \
					GPIOA_Type *GPIOx;    			 \
					uint32_t GPIODIR_DIR_x;          \
					uint32_t GPIOAFSEL_AFSEL_x;      \
					uint32_t GPIODEN_DEN_x;   		 \
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


////////////////////////////////////////////////////////////////////////////////
//                PWM Helper function prototypes follow                       //
////////////////////////////////////////////////////////////////////////////////

// Configuare the sample sequence for the ADC defined within the SS_CFG structure
//void fStartPWM(PWMcfg_t*);
void fStartPWM();
void fStart2PWM();

#endif /* TM4C_UTILS_PWM_HELPER_H_ */
