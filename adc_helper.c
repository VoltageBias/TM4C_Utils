////////////////////////////////////////////////////////////////////////////////
//
// Voltage Bias - the Blog.
// Author: Gilbert Waltoon
//
// Released under a GNU General Public License v3.0
//
// FILENAME : adc_helper.c
// PURPOSE  : A set of helper functions to operate the TM4C123 ADC
//
// Version 0: Oct 30, 2016
// Version 1: Apr 29, 2017 - Added fADCExample(). Writes ADC values to UART
//
////////////////////////////////////////////////////////////////////////////////
#include "TM4C123GH6PM.h"
#include "adc_helper.h"
#include "board_support_package.h"
#include "tm4c_register_fields.h"
#include "uart_helper.h"



////////////////////////////////////////////////////////////////////////////////
//////////////                fADCExample() follows                 ////////////
////////////////////////////////////////////////////////////////////////////////
void fADCExample(){
	fStartUART(UART0, UART0_CFG, baud115200);
	fPrintStringUART(UART0, "\n\r ADC Example ");

	fInitADC(ADC1, AIN2_PE1);
	fPrintStringUART(UART0, "\n\r Finished ADC initialisation ");

	fStartADC(SS_ADC1_AIN2_0);
	fPrintStringUART(UART0, "\n\r Finished Sample Sequence set up... ");

while(1){
};

	return;
}
////////////////////////////////////////////////////////////////////////////////
//////////////                fInitADC() follows                    ////////////
////////////////////////////////////////////////////////////////////////////////
void fInitADC(ADC0_Type* ADCx, AIN_t* AINx)
{
//1. Enable the ADC clock using the RCGCADC register (see page 352).
	if (ADCx == ADC0) {  // if using ADC0
			SYSCTL->RCGCADC |= RCGCADC_R0;
					 }
	else { // ADCx restricted to 2 possible values
			SYSCTL->RCGCADC |= RCGCADC_R1;
					    }
// 2. Enable clock to the appropriate GPIO modules via the RCGCGPIO reg. (p340)
// To find out which GPIO ports to enable, refer to “Signal Description” p801.
	SYSCTL->RCGCGPIO |= (AINx->RCGCGPIO_Rx);

	//set selected pin as an input by clearing bit in GPIODIR
	(AINx->GPIOx)->DIR &=~  (AINx->GPIODIR_DIR_x);

//3. Set the GPIO AFSEL bits for the ADC input pins (see page 671).
// To determine which GPIOs to configure, see Table 23-4 on page 1344
	 (AINx->GPIOx)->AFSEL |= (AINx->GPIOAFSEL_AFSEL_x);

//4. Configure the AINx signals to be analog inputs by clearing the
//   corresponding DEN bit in the GPIO Digital Enable (GPIODEN) register (p682).
	 (AINx->GPIOx)->DEN &=~  (AINx->GPIODEN_DEN_x);

// 5. Disable the analog isolation circuit for all ADC input pins that are to be used by writing a 1 to
//	  the appropriate bits of the GPIOAMSEL register (see page 687) in the associated GPIO block.
	 (AINx->GPIOx)->AMSEL |= (AINx->GPIOAMSEL_GPIOAMSEL_x);

	return;
}
////////////////////////////////////////////////////////////////////////////////
//////////////                fInitADC() ends                       ////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//////////////                fStartADC() follows                   ////////////
////////////////////////////////////////////////////////////////////////////////
void fStartADC(SS_CFG_t *SS_CFGn){

//1. Ensure that the sample sequencer is disabled by clearing the corresponding
// ASENn bit in the ADCACTSS register. Programming of the sample sequencers is
// allowed without having them enabled. Disabling the sequencer during
// programming prevents erroneous execution if a trigger event were to occur
// during the configuration process.
	(SS_CFGn->ADCx)->ACTSS &=~ (SS_CFGn->ASENx);

//2. Conf the trigger event for the sample sequencer in the ADCEMUX register.
	(SS_CFGn->ADCx)->EMUX |= (SS_CFGn->ADCEMUX_EMx);

//3. When using a PWM generator as the trigger source, use the ADC Trigger
//   Source Select (ADCTSSEL) register to specify in which PWM module the
//   generator is located. The default register reset selects PWM module 0
//   for all generators.
//todo code for this

//4. For each sample in the sample sequence, configure the corresponding
// input source in the ADCSSMUXn register.

// Next line fetches SS_CFGn->SSMUXn from the SS_AINn structure.
// 'SS_CFGn->SSMUXn' holds a ptr that points to an adress e.g  "&ADC1->SSMUX3"
// (as defined in the adc_helper.h and TM4C123GH6PM.h) i.e.the address
// of ADC1's SSMUX3 register. We write the SSMUXn_val to this address.

		*(SS_CFGn->SSMUXn) |= SS_CFGn->SSMUXn_val;

//5. For each sample in the sample sequence, configure the sample control bits
// in the corresponding nibble in the ADCSSCTLn register. When programming
// the last nibble, ensure that the END bit is set. Failure to set the END bit
// causes unpredictable behavior.

	    *(SS_CFGn->SSCTLn) |= SS_CFGn->SSCTLn_val;

//6. If interrupts are to be used, set the corresponding
//   MASK bit in the ADCIM register.
	    (SS_CFGn->ADCx)->IM |= SS_CFGn->ADCCIM_MASK;

//7. Enable the sample sequencer logic by setting the corresponding
//   ASENn bit in the ADCACTSS register.
	    (SS_CFGn->ADCx)->ACTSS |= (SS_CFGn->ASENx);

// Clear any pending interrupts
	    (SS_CFGn->ADCx)->ISC |= (SS_CFGn->ADCISC_INx);

// enable the interrupt

	    NVIC_EnableIRQ(ADC1SS3_IRQn);

	return;
}


////////////////////////////////////////////////////////////////////////////////
//////////////                fConstructAINx() follows              ////////////
////////////////////////////////////////////////////////////////////////////////

pAIN_t fConstructAINx(                                         \
		uint32_t uint32RCGCGPIO_Rx,                            \
		GPIOA_Type* gpioGPIOx,                                 \
		uint32_t uint32GPIODIR_DIR_x,                          \
		uint32_t uint32GPIOAFSEL_AFSEL_x,                      \
		uint32_t uint32GPIODEN_DEN_x,                          \
		uint32_t uint32GPIOAMSEL_GPIOAMSEL_x   )
{
	static AIN_t strucAINx; 		//declare a (static) struc variable...
									// ...fill it...
	strucAINx.RCGCGPIO_Rx           = uint32RCGCGPIO_Rx;
	strucAINx.GPIOx                 = gpioGPIOx;
	strucAINx.GPIODIR_DIR_x         = uint32GPIODIR_DIR_x;
	strucAINx.GPIOAFSEL_AFSEL_x     = uint32GPIOAFSEL_AFSEL_x;
	strucAINx.GPIODEN_DEN_x         = uint32GPIODEN_DEN_x;
	strucAINx.GPIOAMSEL_GPIOAMSEL_x = uint32GPIOAMSEL_GPIOAMSEL_x;

	return &strucAINx;              // ...and return a pointer to it
}

////////////////////////////////////////////////////////////////////////////////
//////////////                fConstructAINx() ends                 ////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///              fConstructSS_CFG() follows                                 /////
// This defines the connstructor function that assembles Sample Sequence   /////
// (SS) configuration structures at compile time                           /////
////////////////////////////////////////////////////////////////////////////////
pSS_CFG_t fConstructSS_CFG(                            \
		uint32_t uint32ASENx,                            \
		ADC0_Type* adcADCx,                              \
		uint32_t uint32ADCEMUX_EMx,                      \
		volatile uint32_t* puint32SSMUXn,                \
		uint32_t uint32MUXn_val,                         \
		volatile uint32_t* punit32SSCTLn,                \
		uint32_t uint32SSTCL_val,                        \
		uint32_t uint32ADCCIM_MASK,                      \
		uint32_t uint32ADCISC_INx   )
{
	// Declare a (static) ADC sample sequence structure variable
	static  SS_CFG_t strucSSx;
    // and fill it in...
	strucSSx.ASENx                 = uint32ASENx;
	strucSSx.ADCx                  = adcADCx;
	strucSSx.ADCEMUX_EMx           = uint32ADCEMUX_EMx;
	strucSSx.SSMUXn     		   = puint32SSMUXn;
	strucSSx.SSMUXn_val			   = uint32MUXn_val;
	strucSSx.SSCTLn				   = punit32SSCTLn;
	strucSSx.SSCTLn_val            = uint32SSTCL_val;
	strucSSx.ADCCIM_MASK		   = uint32ADCCIM_MASK;
	strucSSx.ADCISC_INx       	   = uint32ADCISC_INx;
    // ...and return a pointer to it
	return &strucSSx;
}

////////////////////////////////////////////////////////////////////////////////
//////////////                fConstructSS_CFG() ends                ////////////
////////////////////////////////////////////////////////////////////////////////

