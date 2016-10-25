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
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UART_HELPER_H_
#define UART_HELPER_H_

// The TM4C has 8 UART modules. Define them within an enum so that the compiler
// will warn if I try to use  one that I've not got around to coding.
typedef enum  {
	 UART_0   //TODO add others in future as/when they're needed
} UART_modules_t;

// Define allowable baud rates within an enum so that the compiler will warn
// if I try to use one that I've not got around to coding.
 typedef enum  {
	 baud9600,   //TODO add others in future as/when they're needed
	 baud115200
} baud_t;

// Define allowable baud rates within an enum so that the compiler will warn
// if I try to use one that I've not got around to coding.
 typedef enum  {
	 DEC,   //TODO add others in future as/when they're needed
	 HEX
} base_t;


////////////////////////////////////////////////////////////////////////////////
//                UART Helper function prototypes follow                      //
////////////////////////////////////////////////////////////////////////////////

// Startup one ('UART_module) of the TM4C's eight UARTS at 'baud_rate'
// Currently only UART_0 and Baud9600 or Baud115200, 8bit, 1stop bit, no parity
void fstartUART(UART_modules_t, baud_t);

//Prints a char ('ctosend') on one ('UART_module') of the TM4C's eight UARTs
void fprintcharUART(UART_modules_t, char);

//Prints a string ('cpprintme') on one ('UART_module') of the TM4C's eight UARTs
void fprintstringUART(UART_modules_t, char*);

//Returns a char ('cpprintme') from one ('UART_module') of the TM4C's eight UARTs
char fgetCharUART(UART_modules_t);

//Prints an integer ('uint32I') on one ('UART_module') of the TM4C's eight UARTs
//in base_t
void fprintUint32UART(UART_modules_t, uint32_t, base_t);

////////////////////////////////////////////////////////////////////////////////
//                 end of UART Helper function prototypes                     //
////////////////////////////////////////////////////////////////////////////////


#endif /* UART_HELPER_H_ */
