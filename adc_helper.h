////////////////////////////////////////////////////////////////////////////////
//
// VoltageBias - the Blog.
// Author: Gilbert Waltoon
//
// Released under a GNU General Public License v3.0
//
// FILENAME : adc_helper.c
// PURPOSE  : A set of helper functions to operate the TM4C123 ADC
//
// Version 0: Oct 30, 2016
//
////////////////////////////////////////////////////////////////////////////////

#ifndef TM4C_UTILS_ADC_HELPER_H_
#define TM4C_UTILS_ADC_HELPER_H_

#include "TM4C123GH6PM.h"
#include "tm4c_register_fields.h"


////////////////////////////////////////////////////////////////////////////////
//                Definitions of AINx structures follows                      //
////////////////////////////////////////////////////////////////////////////////
//
// When intialising one of the 2xADC's we need to know which board-pins/ports
// that UART uses. We pass this information inside an AINx structure.
//
// For a detailed explanation of the approach to creating structures at compile
// time, see VoltageBias - the Blog - 29 Oct 2016.
//
// The struct. derives from the UART init. procedure p.817 TM4C123GH6PM d'sheet
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
				} AIN_t, *pAIN_t;


pAIN_t fConstructAINx(                                \
			    		uint32_t,                     \
						GPIOA_Type*,                  \
						uint32_t,                     \
						uint32_t,                     \
						uint32_t,                     \
						uint32_t                      \
						 );


// see p801 TM4C123 datasheet
#define AIN2_PE1   ( fConstructAINx (                                  \
									RCGCGPIO_R4,                       \
									GPIOE,                             \
									GPIODIR_DIR_1,                     \
									GPIOAFSEL_AFSEL_1,                 \
									GPIODEN_DEN_1,                     \
									GPIOAMSEL_GPIOAMSEL_1     ))
////////////////////////////////////////////////////////////////////////////////
/////////////        Finished defining UART_CFG structures           ///////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//                ADC Helper function prototypes follow                       //
////////////////////////////////////////////////////////////////////////////////

// Startup one of the TM4C's two ADCs with configuration AINx
void fInitADC(ADC0_Type*, AIN_t*);

#endif /* TM4C_UTILS_ADC_HELPER_H_ */
