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
//
////////////////////////////////////////////////////////////////////////////////
#include "TM4C123GH6PM.h"
#include "adc_helper.h"
#include "board_support_package.h"
#include "tm4c_register_fields.h"

void fInitADC(ADC0_Type* ADCx, AIN_t* AINx)
{
//1. Enable the ADC clock using the RCGCADC register (see page 352).
	if (ADCx == ADC0) {  // if using ADC0
			SYSCTL->RCGCADC |= RCGCADC_R0;
					 }
	else { //no if-else since ADC0_Type already restricted to 2 possible values
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
	 (AINx->GPIOx)->DEN |=  (AINx->GPIODEN_DEN_x);

// 5. Disable the analog isolation circuit for all ADC input pins that are to be used by writing a 1 to
//	  the appropriate bits of the GPIOAMSEL register (see page 687) in the associated GPIO block.
	 (AINx->GPIOx)->AMSEL |= (AINx->GPIOAMSEL_GPIOAMSEL_x);

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
