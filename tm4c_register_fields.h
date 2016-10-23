//////////////////////////////////////////////////////////////////////////////////
//
// Voltage Bias - the Blog.
// Author: Gilbert Waltoon
//
// Released under a GNU General Public License v3.0
//
// FILENAME : tm4c_register_fields.h
// PURPOSE  : A growing set of register bit fields from TM4C123GH6PM datasheet
//
// Version 0: Oct 22, 2016
//
////////////////////////////////////////////////////////////////////////////////

#ifndef TM4C_REGISTER_FIELDS_H_
#define TM4C_REGISTER_FIELDS_H_

#define GPIOAFSEL_AFSEL_0 (1U<<0)
#define GPIOAFSEL_AFSEL_1 (1U<<1)
#define GPIOAFSEL_AFSEL_2 (1U<<2)
#define GPIOAFSEL_AFSEL_3 (1U<<3)
#define GPIOAFSEL_AFSEL_4 (1U<<4)
#define GPIOAFSEL_AFSEL_5 (1U<<5)
#define GPIOAFSEL_AFSEL_6 (1U<<6)
#define GPIOAFSEL_AFSEL_7 (1U<<7)

#define GPIODEN_DEN_0   (1U<<0)
#define GPIODEN_DEN_1   (1U<<1)

#define GPIOPCTL_PMC0_0 (1U<<0)
#define GPIOPCTL_PMC1_0 (1U<<4)

#define RCGCGPIO_R0 (1U<<0)

#define RCGCUART_R0 (1U<<0)

#define UARTCC_CS_0 (1U<<0)
#define UARTCC_CS_1 (1U<<1)
#define UARTCC_CS_2 (1U<<2)
#define UARTCC_CS_3 (1U<<3)

#define UARTCTL_UARTEN (1U<<0)
#define UARTCTL_SIREN (1U<<1)
#define UARTCTL_TXE (1U<<8)
#define UARTCTL_RXE (1U<<9)

#define UARTFR_RXFE (1U<<4)

#define UARTLCRH_PEN (1U<<1)
#define UARTLCRH_EPS (1U<<2)
#define UARTLCRH_STP2 (1U<<3)
#define UARTLCRH_WLEN_1 (1U<<5)
#define UARTLCRH_WLEN_2 (1U<<6)

#define UARTCTL_UARTEN (1U<<0)

#define UARTFR_TXFF (1U<<5)



#endif /* TM4C_REGISTER_FIELDS_H_ */
