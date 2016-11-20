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
/////////////        Finished defining ADC _CFG structures           ///////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//                Definitions of SS_CFG structures follows                    //
////////////////////////////////////////////////////////////////////////////////
//
// Defines a structure (SS_CFGn) that can be passed to the fStartADC() to start
// the ADC sampling.
//
// For a detailed explanation of the approach to creating structures at compile
// time, see VoltageBias - the Blog - 29 Oct 2016.
//
// The struct. derives from the ADC Sample Sequence init. procedure p.817
// TM4C123GH6PM d'sheet
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
typedef struct {    uint32_t ASENx; 			                    \
					ADC0_Type *ADCx;    			                \
					uint32_t ADCEMUX_EMx;                           \
					volatile uint32_t* SSMUXn;                      \
					uint32_t SSMUXn_val;   		                    \
					volatile uint32_t* SSCTLn;                      \
					uint32_t SSCTLn_val;                            \
					uint32_t ADCCIM_MASK;                           \
					uint32_t ADCISC_INx;                            \
			   } SS_CFG_t, *pSS_CFG_t;

// see p801 TM4C123 datasheet
// A concrete example of a Sample Sequence (SS) configuration structure,
// here targettign ADC1 and AIN2
#define SS_ADC1_AIN2_0   ( fConstructSS_CFG (                        \
			ADCACTSS_ASEN3,                                          \
			ADC1,                                                    \
			ADCEMUX_EM3_0|ADCEMUX_EM3_1|ADCEMUX_EM3_2|ADCEMUX_EM3_3, \
			&ADC1->SSMUX3,                 		                     \
			ADCSSMUX3_MUX0_1,                                        \
			&ADC1->SSCTL3,  		                                 \
			ADCSSCTL3_END0|ADCSSCTL3_IE0,                            \
			ADCIM_MASK3,                                             \
			ADCISC_IN3))


// Declare the connstructor function that assembles Sample Sequence (SS)
//  configuration structures at compile time
pSS_CFG_t fConstructSS_CFG(                                 \
							  uint32_t,                     \
							  ADC0_Type*,                   \
							  uint32_t,                     \
							  volatile uint32_t*,           \
							  uint32_t,                     \
							  volatile uint32_t*,           \
							  uint32_t,                     \
							  uint32_t,                     \
							  uint32_t );

////////////////////////////////////////////////////////////////////////////////
/////////////        Finished defining SS_CFG structures           ///////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//                ADC Helper function prototypes follow                       //
////////////////////////////////////////////////////////////////////////////////

// Initiliase one of the TM4C's two ADCs with configuration AINx
void fInitADC(ADC0_Type*, AIN_t*);

// Configuare the sample sequence for the ADC defined within the SS_CFG structure
void fStartADC(SS_CFG_t*);

#endif /* TM4C_UTILS_ADC_HELPER_H_ */
