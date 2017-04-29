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

// See p801 TM4C123 datasheet and p818 for list of all ADC Register
//
// A concrete example Sample Sequence (SS) configuration structure,
// follows, here targetting ADC1 and AIN2(=pin PE1).
// A detailed explanation of the settings is as follows:
//
// ASENx = ADCACTSS_ASEN3.
//       Enable Sample Sequencer 3 (= takes 1 sample, fifo depth=1)
//       A Samp.Sequence is a series of back-to-back samples.
//       Samp.Sequ 0-to-3 differ in no. of samples and fifo depth
//       See Table 13-2.
//       The ADCACTSS Reg. controls activation of SS's 0-to-3 (p.821)
//
//
//  *ADCx = ADC1
//		  Pass in address of the ADC we're using
//
//	ADCEMUX_EMx = ADCEMUX_EM3_0|ADCEMUX_EM3_1|ADCEMUX...
//		 Config. the trigger event for the samp. sequencer (p.804,834).
//       Trig events can be e.g. GPIO event, ContinuousSampling, PWM..
//       Here we set ADCEMUX bits 15:12 = "111" = Continuous Sampling
//
//   SSMUXn = &ADC1->SSMUX3,
//        Pass in the address of SSMUX Reg. for the ADC we're using
//		  (here, we're using Samp.Seq.3. and ADC1)
//        We will write a value ADCSSMUX3_MUX0_1 (= 1U<<1)
//        into the 'MUX0' field of this (ADCSSMUX) Register.
//        "The MUX0 field is used during the 1st sample of a sequence.
//         It specifies which of the analog inputs (a.k.a. pins) is
//		   sampled for the analog-to-digital conversion."
//         The value set indicates the corresponding pin, for example
//         a value of 0x1 indicates the input is AIN1" (p.852)
//
//   SSMUXn_val = ADCSSMUX3_MUX0_1
//			 see above
//
//   SSCTLn = &ADC1->SSCTL3
//          Pass in the address of SSCTRL Reg. for the ADC we're using
//         (here, we're using Samp.Seq.3. and ADC1)
//         We'll write a value ADCSSCTL3_END0|ADCSSCTL3_IE0 to this reg.
//         = "The raw interrupt signal (INR0 bit) is asserted at the end
//			  of the 1st sample's conversion. If the MASK0 bit in the
//			  ADCIM register is set, the interrupt is promoted to the
//			  interrupt controller"
//           "The 1st sample is the last sample of the sequence" (p859)
//
// 	 SSCTLn_val = ADCSSCTL3_END0|ADCSSCTL3_IE0,
//			See above
//
//   ADCCIM_MASK = ADCIM_MASK3
//	        "If the MASK0 bit in the ADCIM register is set, the interrupt
//			 is promoted to the interrupt controller"
//
//   ADCISC_INx = ADCISC_IN3
//			Will be used to clear any pending interrupts
//          ADCISC_IN3= 1<<3
//          This field of the ADCISC field corresponds to the
//		    SS3 Interrupt Status and Clear. This bit is cleared by
//          writing a '1'.
//
	#define SS_ADC1_AIN2_0   ( fConstructSS_CFG (                    \
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

// Call to run an example. Writes ADC values to the UART@115200Baud
void fADCExample();

#endif /* TM4C_UTILS_ADC_HELPER_H_ */
