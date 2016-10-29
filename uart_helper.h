//////////////////////////////////////////////////////////////////////////////////
//
// Voltage Bias - the Blog.
// Author: Gilbert Waltoon
//
// Released under a GNU General Public License v3.0
//
// FILENAME : uart_helper.h
// PURPOSE  : A set of helper functions to operate the TM4C123 UART
//
// Version 0: Oct 22, 2016
// Version 1: Oct 25, 2016  - Added fprintUint32UART()
// Version 2: Oct 29, 2016  - Major rewrite of all function prototypes to take
//							  UART0_Types, UARTConfig_t arguments
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UART_HELPER_H_
#define UART_HELPER_H_

#include "TM4C123GH6PM.h"
#include "tm4c_register_fields.h"

////////////////////////////////////////////////////////////////////////////////
///////////////////////////Define UART_CFG structures///////////////////////////
//
// When intialising one of the 8xUART's we need to know which board-pins/ports
// that UART uses.It's natural to consider creating 8 structures
// ('UART0_CFG'... 'UART7_CFG') to hold this data.
// A downside is we would then have 8 structures in memory, even if our code
// used only one (UART0_CFG, say).
// Instead, we'd like to 'construct' only those UART_CFG's our code uses...
//
// We define a function fConstructStaticUART_CFG('Pin/Port data') that takes
// pin/port-data and returns a UARTx_CFG structure contaning this data.
// Next, we
//    #define UART0_CFG  fConstructStaticUART_CFG('Port data for UART0')
// Now, whenever we write 'UART0_CFG', the compiler replaces it with a call to
// our function returning a structure containing said 'Port data for UART0'
//
// The struct. derives from the UART init. procedure p.902 TM4C123GH6PM d'sheet
// struct {
//  uint32_t RCGCUART_Rx;   "Enable UART module using the RCGCUART reg."
//  uint32_t RCGCGPIO_Rx;   "Enable clk to appropriate GPIO via RCGCGPIO reg."
//  GPIOA_Type *GPIOx;      The port used  by the GPIO
//  uint32_t GPIOAFSEL_AFSEL_x; "Set GPIO AFSEL bits for the appropriate pins"
//  uint32_t GPIOPCTL_PMCx_x;  "Conf. PMCn fields in GPIOPCTL reg. to assign..
//  uint32_t GPIODEN_DEN_x;     ...UART signals to the appropriate"
//        }
	typedef struct {
		uint32_t RCGCUART_Rx;                                                \
		uint32_t RCGCGPIO_Rx;                                                \
		GPIOA_Type *GPIOx;                                                   \
		uint32_t GPIOAFSEL_AFSEL_x;                                          \
		uint32_t GPIOPCTL_PMCx_x;                                            \
		uint32_t GPIODEN_DEN_x;                                              \
	} UARTConfig_t, *pUARTConfig_t;


	pUARTConfig_t fConstructStaticUART_CFG(uint32_t,                         \
		                                uint32_t,                            \
										GPIOA_Type* ,                        \
										uint32_t,                            \
										uint32_t,                            \
										uint32_t);

// UART0 uses PA0(Rx), PA1(Tx)
#define UART0_CFG  ( fConstructStaticUART_CFG(                               \
                           RCGCUART_R0,                                      \
						   RCGCGPIO_R0,                                      \
						   GPIOA,                                            \
						   (GPIOAFSEL_AFSEL_0|GPIOAFSEL_AFSEL_1),            \
						   (GPIOPCTL_PMC0_0|GPIOPCTL_PMC1_0),                \
						   (GPIODEN_DEN_0|GPIODEN_DEN_1)      ))

// todo add #define UART1_CFG.... etc. here as needed.

////////////////////////////////////////////////////////////////////////////////
///////////////////////Finished defining UART_CFG structures////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//                UART Helper function prototypes follow                      //
////////////////////////////////////////////////////////////////////////////////

// Startup one ('UART_module) of the TM4C's eight UARTS at 'baud_rate'
// Currently only UART_0 and Baud9600 or Baud115200, 8bit, 1stop bit, no parity
	typedef enum  {
	 	 baud9600,                                  //TODO add others as needed
	 	 baud115200 } baud_t;
	 void fStartUART(UART0_Type*, UARTConfig_t*, baud_t);

//Prints a char on one of the TM4C's eight UARTs
	void fPrintCharUART(UART0_Type*, char);

//Prints a string on one  of the TM4C's eight UARTs
	void fPrintStringUART(UART0_Type*, char*);

//Returns a char from one ('UART_module') of the TM4C's eight UARTs
	char fGetCharUART(UART0_Type*);

//Prints an integer ('uint32I') on one ('UART_module') of the TM4C's eight UARTs
//in base_t
	typedef enum  {
	 	 DEC,                                        //TODO add others as needed
	 	 HEX } base_t;
	void fPrintUint32UART(UART0_Type*, uint32_t, base_t);

//Show example use of uart_helper.c functions
	void fUartHelperExample();

////////////////////////////////////////////////////////////////////////////////
//                 end of UART Helper function prototypes                     //
////////////////////////////////////////////////////////////////////////////////



#endif /* UART_HELPER_H_ */
