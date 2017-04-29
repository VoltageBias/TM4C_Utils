////////////////////////////////////////////////////////////////////////////////
//
// Voltage Bias - the Blog.
// Author: Gilbert Waltoon
//
// Released under a GNU General Public License v3.0
//
// FILENAME : board_suppoprt_package.c
// PURPOSE  : Interrupt handlers
//
// Version 0: Apr 29, 2017
//
////////////////////////////////////////////////////////////////////////////////

/* Board Support Package */
#include "TM4C123GH6PM.h"
#include "board_support_package.h"
#include "uart_helper.h"

__attribute__((naked)) void assert_failed (char const *file, int line) {
    /* TBD: damage control */
    NVIC_SystemReset(); /* reset the system */
}

void SysTick_Handler(void) {
 //   GPIOF_AHB->DATA_Bits[LED_BLUE] ^= LED_BLUE;
}

////////////////////////////////////////////////////////////////////////////////
//////////////                ADC1Seq3_IRQHandler() follows         ////////////
/////////////                 Interrupt handler for ADC1            ////////////
////////////////////////////////////////////////////////////////////////////////
volatile static uint32_t adcResult;
void ADC1Seq3_IRQHandler(void){
	{
	  adcResult = ADC1 -> SSFIFO3;
	  adcResult &= 0xFFF; //Only the lower 12bits meaningful
	  fPrintUint32UART(UART0, adcResult, DEC); fPrintStringUART(UART0,"\n\r");
	  ADC1->ISC |= (1U<<3);
	}
}
////////////////////////////////////////////////////////////////////////////////
//////////////              ADC1Seq3_IRQHandler() ends              ////////////
////////////////////////////////////////////////////////////////////////////////


