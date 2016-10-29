////////////////////////////////////////////////////////////////////////////////
//
// Voltage Bias - the Blog.
// Author: Gilbert Waltoon
//
// Released under a GNU General Public License v3.0
//
// FILENAME : uart_helper.c
// PURPOSE  : A set of helper functions to operate the TM4C123 UART
//
// Version 0: Oct 22, 2016
// Version 1: Oct 25, 2016  - Added fprintUint32UART()
// Version 2: Oct 29, 2016  - Major rewrite of all function prototypes to take
//							  UART0_Types, UARTConfig_t arguments
////////////////////////////////////////////////////////////////////////////////

#include "TM4C123GH6PM.h"
#include "uart_helper.h"
#include "board_support_package.h"
#include "tm4c_register_fields.h"

////////////////////////////////////////////////////////////////////////////////
// fprintcharUART() follows
// Purpose: Prints a single character ('ctosend') on one ('UART_module')
//          of the TM4C's eight UARTs
//
////////////////////////////////////////////////////////////////////////////////
void fPrintCharUART(UART0_Type *UARTx, char cPrintMe){

	while( (UARTx->FR & UARTFR_TXFF) != 0 )
	{
		//do nothing
	};

	UARTx->DR = cPrintMe;

    return;
}
///////////////////////fprintcharUART ends//////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// fprintstringUART() follows
// Purpose: Prints a string ('cpprintme') on one ('UART_module')
//          of the TM4C's eight UARTs
//
////////////////////////////////////////////////////////////////////////////////

void fPrintStringUART(UART0_Type* UARTx, char *strPrintMe){
	while(*strPrintMe) {
		 	 	 	 	 fPrintCharUART(UARTx, *(strPrintMe++));
					   }
	return;
}

///////////////////////fprintstringUART ends////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////
// fgetcharUART() follows
// Purpose: Returns a char read from one ('UART_module') of the TM4C's UARTs
//
////////////////////////////////////////////////////////////////////////////////
char fGetCharUART(UART0_Type* UARTx){
	char cReturnMe;

			while( (UARTx->FR & UARTFR_RXFE) != 0) {}; //loop, waiting for char
			cReturnMe = UARTx->DR;   // retreive the newly arrived char

	return cReturnMe;
}
///////////////////////fgetcharUART() ends//////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// fprintUint32UART() follows
// Purpose: Prints a 'uint32I' on one ('UART_module') of the TM4C's eight UARTs
//          in 'base' (= DEC or HEX)
////////////////////////////////////////////////////////////////////////////////
void fPrintUint32UART(UART0_Type *UARTx, uint32_t uint32Int2Prnt, base_t base)
{
	 const char digit[] = "0123456789ABCDEF";
	 uint32_t baseVal;
	 uint32_t divDown;
	 char cStringifiedInt2Prnt[14];
	 char* pcStringifiedInt2Prnt = cStringifiedInt2Prnt;

	switch(base)
			{
			case HEX:
				  baseVal = 16;
				  *pcStringifiedInt2Prnt++ = '0';
				  *pcStringifiedInt2Prnt++ = 'x';
			break;

			case DEC:
				  baseVal = 10;
			break;
			//TODO code other module cases here as required.
			default:
				 baseVal = 10;
			break;
			}
	divDown = uint32Int2Prnt;
    do{  // work out number of places needed by repeated divide-by-ten(or 16)
        divDown = divDown / baseVal;
        ++pcStringifiedInt2Prnt; //increment ptr as we go
    } while(divDown);

    *pcStringifiedInt2Prnt = '\0';  //write terminating char

    do{     //Move back through string inserting digits
   	*--pcStringifiedInt2Prnt= digit[uint32Int2Prnt%baseVal];
    	uint32Int2Prnt = uint32Int2Prnt/baseVal;
    } while(uint32Int2Prnt);

    //now print the string
	fPrintStringUART(UARTx, cStringifiedInt2Prnt);
	return;
}
/////////////////////// fprintUint32UART()//////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
// fstartUART() follows
// Purpose: Startup one ('UART_module) of the TM4C's eight UARTS.
//          with Baud rate ('baud_rate)
// N.B Currently only configures UART_0 for Baud9600 or Baud115200
//     and 8bit, 1stop bit, no parity
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void fStartUART(UART0_Type *UARTx, UARTConfig_t *UARTxCfg, baud_t baud_rate){

// See page 902 of the TI TM4C123GH6PM datasheet.
	  SYSCTL->RCGCUART |= (UARTxCfg->RCGCUART_Rx);

//Enable the clock to the appropriate GPIO module via RCGCGPIO reg. (p340).
//To find out which GPIO port to enable, refer to Table 23-5 on page 1351.
	  SYSCTL->RCGCGPIO |= (UARTxCfg->RCGCGPIO_Rx);

// Set the GPIO AFSEL bits for the appropriate pins (see page 671).
// To determine which GPIOs to configure, see Table 23-4 on page 1344
	  (UARTxCfg->GPIOx)->AFSEL |= (UARTxCfg->GPIOAFSEL_AFSEL_x);

//4. Configure the GPIO current level and/or slew rate as specified for mode
//   selected (see page 673 and page 681).

//5. Configure the PMCn fields in the GPIOPCTL register to assign the
//   UART signals to the appropriatepins (see p688 and Table 23-5 on p1351)
	   (UARTxCfg->GPIOx)->PCTL |= (UARTxCfg->GPIOPCTL_PMCx_x);
	   (UARTxCfg->GPIOx)->DEN  |= (UARTxCfg->GPIODEN_DEN_x);

// Get ready to set baud rate...
// Disable the UART by clearing the UARTEN bit in the UARTCTL register.
	     UARTx->CTL &=~UARTCTL_UARTEN;

// Declare some variables to hold integer and fractional baud rate settings
// Use the datasheet formualae p896
// BRD = BRDI + BRDF = UARTSysClk / (ClkDiv * Baud Rate)
		uint32_t ui32BRDI;
		uint32_t ui32BRDF;
		uint32_t ui32baud;
		switch(baud_rate)
			   {
			    case baud9600:
			    	ui32baud = 9600;
			    break;
			    case baud115200:
			    	ui32baud = 115200;
			    break;
			   //TODO code other baud cases here as required.
			   // High speeds may require additional reg. configs.
			   // - refer to datasheet
			    default:
			    	ui32baud = 9600;
			   break;
			    }
//TODO For high speed operation, formula may need revising.
		ui32BRDI = ( SYS_CLOCK_HZ / (16 * ui32baud) );
		ui32BRDF = ((((SYS_CLOCK_HZ * 8 / ui32baud) + 1 ) /2) % 64);
	    UARTx->IBRD = ui32BRDI;

//3. Write the fractional portion of the BRD to the UARTFBRD register.
	   UARTx->FBRD = ui32BRDF;

//4. Write the desired serial parameters to the UARTLCRH register
	UARTx->LCRH |= (UARTLCRH_WLEN_2|UARTLCRH_WLEN_1);             //8bit
	UARTx->LCRH &= ~UARTLCRH_STP2;                                //1 stop bit
	UARTx->LCRH  &= ~UARTLCRH_PEN ;                               //no parity

//5. Configure the UART clock source by writing to the UARTCC register.
//   Use system clk
	UARTx->CC &=~(UARTCC_CS_3|UARTCC_CS_2|UARTCC_CS_1|UARTCC_CS_0);

//6. Optionally, configure  DMA (see “Micro Direct Memory Access" p585)
//   and enable the DMA option(s) in the UARTDMACTL register.

//7. Enable the UART by setting the UARTEN bit in the UARTCTL register.
	UARTx->CTL |= (UARTCTL_UARTEN| UARTCTL_TXE| UARTCTL_RXE);

	return;
}

///////////////////////fstartUART ends//////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// fUartHelperExamples() follows
// Purpose : Show example use of uart_helper.c functions
//
////////////////////////////////////////////////////////////////////////////////
void fUartHelperExample(){
  char cKeyPress;

  fStartUART(UART0, UART0_CFG, baud115200);

  fPrintStringUART(UART0, "\n\r Here's 127 in decimal: ");
  fPrintUint32UART(UART0, 127, DEC); fPrintStringUART(UART0,"\n\r");
  fPrintStringUART(UART0, " Here it is in hex: ");
  fPrintUint32UART(UART0, 127, HEX); fPrintStringUART(UART0,"\n\r");

  while(1){  									//echo key-presses on UART0
	 	fPrintStringUART(UART0, " Press a key ");
	 	cKeyPress = fGetCharUART(UART0); fPrintStringUART(UART0,"\n\r");
	 	fPrintStringUART(UART0, " You pressed ");
	 	fPrintCharUART(UART0, cKeyPress); fPrintStringUART(UART0,"\n\r");
	       }

return;
}
///////////////////////main() ends//////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//todo write description
pUARTConfig_t fConstructStaticUART_CFG(uint32_t uint32RCGCUART_Rx,            \
										uint32_t uint32RCGCGPIO_Rx,           \
										GPIOA_Type* gpioGPIOx,				  \
										uint32_t uint32GPIOAFSEL_AFSEL_x,     \
										uint32_t unint32GPIOPCTL_PMCx_x,      \
										uint32_t uint32GPIODEN_DEN_x          \
										)
{
	static UARTConfig_t strucUartx_Cfg; //declare a (static) structure variable...
	                                    // ...fill it in...
	strucUartx_Cfg.RCGCUART_Rx       = uint32RCGCUART_Rx;
	strucUartx_Cfg.RCGCGPIO_Rx       = uint32RCGCGPIO_Rx;
	strucUartx_Cfg.GPIOx             = gpioGPIOx;
	strucUartx_Cfg.GPIOAFSEL_AFSEL_x = uint32GPIOAFSEL_AFSEL_x;
	strucUartx_Cfg.GPIOPCTL_PMCx_x   = unint32GPIOPCTL_PMCx_x;
	strucUartx_Cfg.GPIODEN_DEN_x     = uint32GPIODEN_DEN_x;

	return &strucUartx_Cfg;              // ...and return a pointer to it
}

