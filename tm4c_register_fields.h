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

#define ADCACTSS_ASEN0 (1U<<0)
#define ADCACTSS_ASEN1 (1U<<1)
#define ADCACTSS_ASEN2 (1U<<2)
#define ADCACTSS_ASEN3 (1U<<3)

#define ADCEMUX_EM0_0 (1U<<0)
#define ADCEMUX_EM0_1 (1U<<1)
#define ADCEMUX_EM0_2 (1U<<2)
#define ADCEMUX_EM0_3 (1U<<3)

#define ADCEMUX_EM1_0 (1U<<4)
#define ADCEMUX_EM1_1 (1U<<5)
#define ADCEMUX_EM1_2 (1U<<6)
#define ADCEMUX_EM1_3 (1U<<7)

#define ADCEMUX_EM2_0 (1U<<8)
#define ADCEMUX_EM2_1 (1U<<9)
#define ADCEMUX_EM2_2 (1U<<10)
#define ADCEMUX_EM2_3 (1U<<11)

#define ADCEMUX_EM3_0 (1U<<12)
#define ADCEMUX_EM3_1 (1U<<13)
#define ADCEMUX_EM3_2 (1U<<14)
#define ADCEMUX_EM3_3 (1U<<15)

#define ADCIM_MASK0 (1U<<0)
#define ADCIM_MASK1 (1U<<1)
#define ADCIM_MASK2 (1U<<2)
#define ADCIM_MASK3 (1U<<3)
#define ADCIM_DCONSS0 (1U<<16)
#define ADCIM_DCONSS1 (1U<<17)
#define ADCIM_DCONSS2 (1U<<18)
#define ADCIM_DCONSS3 (1U<<19)

#define ADCISC_IN0 (1U<<0)
#define ADCISC_IN1 (1U<<1)
#define ADCISC_IN2 (1U<<2)
#define ADCISC_IN3 (1U<<3)
#define ADCISC_DCINSS0 (1U<<16)
#define ADCISC_DCINSS1 (1U<<17)
#define ADCISC_DCINSS2 (1U<<18)
#define ADCISC_DCINSS3 (1U<<19)

#define ADCSSCTL3_D0   (1U<<0)
#define ADCSSCTL3_END0 (1U<<1)
#define ADCSSCTL3_IE0  (1U<<2)
#define ADCSSCTL3_TS0  (1U<<3)

#define ADCSSMUX3_MUX0_0 (1U<<0)
#define ADCSSMUX3_MUX0_1 (1U<<1)
#define ADCSSMUX3_MUX0_2 (1U<<2)
#define ADCSSMUX3_MUX0_3 (1U<<3)

#define CPAC_CP10_0 (1U<<20)
#define CPAC_CP10_1 (1U<<21)
#define CPAC_CP11_0 (1U<<22)
#define CPAC_CP11_1 (1U<<23)

#define FPCC_LSPEN (1U<<30)
#define FPCC_ASPEN (1U<<31)

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

#define GPIODIR_DIR_0 (1U<<0)
#define GPIODIR_DIR_1 (1U<<1)
#define GPIODIR_DIR_2 (1U<<2)
#define GPIODIR_DIR_3 (1U<<3)
#define GPIODIR_DIR_4 (1U<<4)
#define GPIODIR_DIR_5 (1U<<5)
#define GPIODIR_DIR_6 (1U<<6)
#define GPIODIR_DIR_7 (1U<<7)

#define GPIOAMSEL_GPIOAMSEL_0 (1U<<0)
#define GPIOAMSEL_GPIOAMSEL_1 (1U<<1)
#define GPIOAMSEL_GPIOAMSEL_2 (1U<<2)
#define GPIOAMSEL_GPIOAMSEL_3 (1U<<3)
#define GPIOAMSEL_GPIOAMSEL_4 (1U<<4)
#define GPIOAMSEL_GPIOAMSEL_5 (1U<<5)
#define GPIOAMSEL_GPIOAMSEL_6 (1U<<6)
#define GPIOAMSEL_GPIOAMSEL_7 (1U<<7)

#define GPIOPCTL_PMC0_0 (1U<<0)
#define GPIOPCTL_PMC1_0 (1U<<4)

#define RCGCADC_R0 (1U<<0)
#define RCGCADC_R1 (1U<<1)

#define RCGCGPIO_R0 (1U<<0)
#define RCGCGPIO_R1 (1U<<1)
#define RCGCGPIO_R2 (1U<<2)
#define RCGCGPIO_R3 (1U<<3)
#define RCGCGPIO_R4 (1U<<4)
#define RCGCGPIO_R5 (1U<<5)

#define RCGCUART_R0 (1U<<0)
#define RCGCUART_R1 (1U<<1)
#define RCGCUART_R2 (1U<<2)
#define RCGCUART_R3 (1U<<3)
#define RCGCUART_R4 (1U<<4)
#define RCGCUART_R5 (1U<<5)
#define RCGCUART_R6 (1U<<6)
#define RCGCUART_R7 (1U<<7)

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
