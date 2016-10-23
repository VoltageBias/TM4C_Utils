//////////////////////////////////////////////////////////////////////////////////
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
//
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

void fprintcharUART(UART_modules_t UART_module, char ctosend) {

	switch(UART_module)
	{
	case UART_0:
		while( (UART0->FR & UARTFR_TXFF) != 0 );
		 UART0->DR = ctosend;
	break;
				//TODO code other module cases here as required.
	default:
		while((UART0->FR & UARTFR_TXFF) != 0);
		UART0->DR = ctosend;
	break;
	}

	return;
}
///////////////////////fprintcharUART ends/////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// fprintcharUART() follows
// Purpose: Prints a string ('cpprintme') on one ('UART_module')
//          of the TM4C's eight UARTs
//
////////////////////////////////////////////////////////////////////////////////

void fprintstringUART(UART_modules_t UART_module, char *cpprintme)
{

	while(*cpprintme)
	  {fprintcharUART(UART_module, *(cpprintme++));
	  }
  	return;
}

///////////////////////fprintcharUART ends//////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// fgetcharUART() follows
// Purpose: Returns a char read from one ('UART_module') of the TM4C's UARTs
//
////////////////////////////////////////////////////////////////////////////////
char fgetCharUART(UART_modules_t UART_module){

	char cReturnMe;

	switch(UART_module)
		{
		case UART_0:
			while( (UART0->FR & UARTFR_RXFE) != 0) {}; //loop, waiting for char
			cReturnMe = UART0->DR;   // retreive the newly arrived char
		break;
					//TODO code other module cases here as required.
		default:
			while( (UART0->FR & UARTFR_RXFE) != 0) {}; //loop, waiting for char
			cReturnMe = UART0->DR;   // retreive the newly arrived char
		break;
		}

	return cReturnMe;
}
///////////////////////fgetcharUART() ends//////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// fstartUART() follows
// Purpose: Startup one ('UART_module) of the TM4C's eight UARTS.
//          with Baud rate ('baud_rate)
// N.B Currently only configures UART_0 for Baud9600 or Baud115200
//     and 8bit, 1stop bit, no parity
////////////////////////////////////////////////////////////////////////////////

void fstartUART(UART_modules_t UART_module, baud_t baud_rate){
	// See page 902 of the TI TM4C123GH6PM datasheet.

	// Rather than code multuple switch/case here, there is probably a neater way
	// to select amongst the UART module through offset vectors.
	// ...but this works and is a simple enough.

	//Enable the UART module using the RCGCUART register (see page 344).
	switch(UART_module)
	{
		case UART_0:
	    	  SYSCTL->RCGCUART |= RCGCUART_R0;
	    break;
	   //TODO code other module cases here as required.
	    default:
	    	  SYSCTL->RCGCUART |= RCGCUART_R0;
	   break;
	    }

	//Enable the clock to the appropriate GPIO module via the RCGCGPIO register (see page 340).
	//To find out which GPIO port to enable, refer to Table 23-5 on page 1351.
	switch(UART_module)
	{
		case UART_0:
			SYSCTL->RCGCGPIO |= RCGCGPIO_R0; //port A
		break;
		   //TODO code other module cases here as required.
		default:
			SYSCTL->RCGCGPIO |= RCGCGPIO_R0; //port A
		break;
		    }

	//Set the GPIO AFSEL bits for the appropriate pins (see page 671). To determine which GPIOs to
	//configure, see Table 23-4 on page 1344
	switch(UART_module)
		   {
		    case UART_0:
		    	  GPIOA->AFSEL |= (GPIOAFSEL_AFSEL_0|GPIOAFSEL_AFSEL_1) ; //set pins PA0,PA1 to alternate UART function
		    break;
		   //TODO code other module cases here as required.
		    default:
		    	  GPIOA->AFSEL |= (GPIOAFSEL_AFSEL_0|GPIOAFSEL_AFSEL_1); //set pins PA0,PA1 to alternate UART function
		   break;
		    }


		//4. Configure the GPIO current level and/or slew rate as specified for the mode selected (see
		//page 673 and page 681).

		//  5. Configure the PMCn fields in the GPIOPCTL register to assign the UART signals to the appropriate
		//pins (see page 688 and Table 23-5 on page 1351).

	switch(UART_module)
		   {
		    case UART_0:

		    	  GPIOA->PCTL |=GPIOPCTL_PMC0_0|GPIOPCTL_PMC1_0;
		    	  GPIOA->DEN  |=GPIODEN_DEN_0|GPIODEN_DEN_1;  //enable the digital function for the UART pins
		    break;
		   //TODO code other module cases here as required.
		    default:
		    	 GPIOA->PCTL |=GPIOPCTL_PMC0_0|GPIOPCTL_PMC1_0;
		    	 GPIOA->DEN  |=GPIODEN_DEN_0|GPIODEN_DEN_1;  //enable the digital function for the UART pins
		   break;
		    }

		//get ready to set baud rate...
		// Disable the UART by clearing the UARTEN bit in the UARTCTL register.
		switch(UART_module)
			   {
			    case UART_0:
			    	UART0->CTL &=~UARTCTL_UARTEN;
			    break;
			   //TODO code other module cases here as required.
			    default:
			    	UART0->CTL &=~UARTCTL_UARTEN;
			   break;
			    }


		//declare a couple of variables to hold integer and fractional baud rate settings
		//Use the datasheet formualae p896
		//BRD = BRDI + BRDF = UARTSysClk / (ClkDiv * Baud Rate)

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
			   //TODO code other module cases here as required.
			    default:
			    	ui32baud = 9600;
			   break;
			    }
		ui32BRDI = ( SYS_CLOCK_HZ / (16 * ui32baud) ); //TODO For high speed operation, formula may need revising.
		ui32BRDF = ((((SYS_CLOCK_HZ * 8 / ui32baud) + 1 ) /2) % 64);

		//2. Write the integer portion of the BRD to the UARTIBRD register.
		switch(UART_module)
					   {
					    case UART_0:
					    	 UART0->IBRD = ui32BRDI;
					    break;
					   //TODO code other module cases here as required.
					    default:
					    	 UART0->IBRD = ui32BRDI;
					   break;
					    }

		//3. Write the fractional portion of the BRD to the UARTFBRD register.
		switch(UART_module)
					   {
					    case UART_0:
					    	 UART0->FBRD = ui32BRDF;
					    break;
					   //TODO code other module cases here as required.
					    default:
					    	 UART0->FBRD= ui32BRDF;
					   break;
					    }



	//4. Write the desired serial parameters to the UARTLCRH register (in this case, a value of
	//0x0000.0060).
		switch(UART_module)
		{
			case UART_0:
				UART0->LCRH |= (UARTLCRH_WLEN_2|UARTLCRH_WLEN_1);  //8bit, no parity, 1 stop bit
				UART0->LCRH &= ~UARTLCRH_STP2; //1 stop bit
				UART0->LCRH  &= ~UARTLCRH_PEN ; //no parity

				//UART0->LCRH = (0x3<<5); //8bit, no parity, 1 stop bit
			break;
				//TODO code other module cases here as required.
			default:
				UART0->LCRH |= (UARTLCRH_WLEN_2|UARTLCRH_WLEN_1);  //8bit, no parity, 1 stop bit
				UART0->LCRH &= ~UARTLCRH_STP2; //1 stop bit
				UART0->LCRH  &= ~UARTLCRH_PEN ; //no parity
			break;
		}


	//5. Configure the UART clock source by writing to the UARTCC register.
		switch(UART_module)
		 {
			case UART_0:
				UART0->CC &=~(UARTCC_CS_3|UARTCC_CS_2|UARTCC_CS_1|UARTCC_CS_0); //use system clock
			break;
				//TODO code other module cases here as required.
			default:
				UART0->CC &=~(UARTCC_CS_3|UARTCC_CS_2|UARTCC_CS_1|UARTCC_CS_0);
			break;
				 }



	//6. Optionally, configure the µDMA channel (see “Micro Direct Memory Access (µDMA)” on page 585)
	//and enable the DMA option(s) in the UARTDMACTL register.


	//7. Enable the UART by setting the UARTEN bit in the UARTCTL register.
		switch(UART_module)
				 {
					case UART_0:
						 UART0->CTL |= (UARTCTL_UARTEN| UARTCTL_TXE| UARTCTL_RXE);
					break;
						//TODO code other module cases here as required.
					default:
						UART0->CTL |= (UARTCTL_UARTEN| UARTCTL_TXE| UARTCTL_RXE);
					break;
						 }


	return;
}

///////////////////////fstartUART ends///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


