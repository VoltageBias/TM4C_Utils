//////////////////////////////////////////////////////////////////////////////////
//
// Voltage Bias - the Blog.
// Author: Gilbert Waltoon
//
// Released under a GNU General Public License v3.0
//
// FILENAME : UART_example.c
// PURPOSE  : Example of TM4C123 UART communication using uart_helper.c functions
//
// Version 0: Oct 25, 2016
//
////////////////////////////////////////////////////////////////////////////////

#include "TM4C123GH6PM.h"
#include "board_support_package.h"
#include "uart_helper.h"

////////////////////////////////////////////////////////////////////////////////
// main() follows
// Purpose : Show example use of uart_helper.c functions
//
////////////////////////////////////////////////////////////////////////////////
int main()
{
  char cKeyPress;

  fstartUART(UART_0, baud115200);   				//start UART0, 115200Hz

  fprintstringUART(UART_0, "\n\r Here's 1234 in decimal: ");
  fprintUint32UART(UART_0, 1234, DEC); fprintstringUART(UART_0,"\n\r");
  fprintstringUART(UART_0, " Here it is in hex: ");
  fprintUint32UART(UART_0, 1234, HEX); fprintstringUART(UART_0,"\n\r");

  while(1){  										//echo key-presses on UART0
	  fprintstringUART(UART_0, " Press a key ");
	  cKeyPress = fgetCharUART(UART_0); fprintstringUART(UART_0,"\n\r");
	  fprintstringUART(UART_0, " You pressed ");
	  fprintcharUART(UART_0, cKeyPress); fprintstringUART(UART_0,"\n\r");
      }
  return 0;
}
///////////////////////main() ends///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

