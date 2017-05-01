////////////////////////////////////////////////////////////////////////////////
//
// Voltage Bias - the Blog.
// Author: Gilbert Waltoon
//
// Released under a GNU General Public License v3.0
//
// FILENAME : pwm_helper.c
// PURPOSE  : A set of helper functions to operate the TM4C123 PWM
//          : currently only outputs on pins PB6, PB7
//
// Version 0: 1st May 2017
//
////////////////////////////////////////////////////////////////////////////////
#include "TM4C123GH6PM.h"
#include "board_support_package.h"
#include "tm4c_register_fields.h"
#include "uart_helper.h"
#include "pwm_helper.h"

////////////////////////////////////////////////////////////////////////////////
//////////////                fPWMExample() follows            ////////////
////////////////////////////////////////////////////////////////////////////////

// Call to run an example. Writes ADC values to the UART@115200Baud
void fPWMExample(){
    fStartUART(UART0, UART0_CFG, baud115200);
    fPrintStringUART(UART0, "\n\r Starting PWM Example.....: ");

// For a Desired PWM Frequency and Duty [0..1] pass in:
//
// ui32_PWM0LOAD = ( SYS_CLOCK_HZ / 2xDesired-frequency ) - 1
// ui32_PWM0CMPA = ((1 - Desired-duty-PWM_A) x (SYS_CLOCK_HZ / 2xDesired-freq.))-1
// ui32_PWM0CMPA = ((1 - Desired-duty-PWM_B) x (SYS_CLOCK_HZ / 2xDesired-freq.))-1
//
// For example, for desired 25kHz, PWMa= 0.25, PWMb = 0.75 duty, SYS_CLOCK_HZ=16MHz
//   ui32_PWM0LOAD = 16,000,000/(2x25,000) - 1 =  319
//   ui32_PWM0CMPA = ( (1-0.25) x 320 ) - 1 = 239
//   ui32_PWM0CMPB = ( (1-0.75) x 320 ) - 1 = 79

    fStartPWM(319, 239, 79);
    while(1){};
    return;
 }
////////////////////////////////////////////////////////////////////////////////
//////////////                fPWMExample() ends                    ////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//////////////                fStartPWM() follows                   ////////////
////////////////////////////////////////////////////////////////////////////////
void fStartPWM(uint32_t ui32_PWM0LOAD,        \
               uint32_t ui32_PWM0CMPA,        \
               uint32_t ui32_PWM0CMPB ) {
 // Shows shows how to initialize PWM Gen. 0 with a 25-kHz, 25% duty cycle on
 // MnPWM0 pin, and 75% duty on MnPWM1 pin. Assumes system clock is 16 MHz.
 // M0PWM0 = PB6(4) pin no.1
 // M0PWM1 = PB7(4) pin no.4

//  p1239, Enable the PWM clock by writing 0x0010.0000 to the RCGC0 p456
     SYSCTL->RCGC0 = RCGC0_PWM0;
    // SYSCTL->RCGCPWM = (1U<<0);
     //RCGCPWM

// Enable the clock to the appropriate GPIO module via RCGC2 (p.464)
     SYSCTL->RCGC2 |= RCGC2_GPIOB;
    //SYSCTL->RCGCGPIO |= (1U<<1);

// In GPIO module, enable the  pins for alt. func. using GPIOAFSEL (p671)
    GPIOB->AFSEL |= ( GPIOAFSEL_AFSEL_6 | GPIOAFSEL_AFSEL_7 );

// Config. PMCn fields in GPIOPCTL (p689) to assign PWM sigs to pins
   GPIOB->PCTL &=~( (GPIOPCTL_PMC6_0)|(GPIOPCTL_PMC6_1)|(GPIOPCTL_PMC6_3) | \
                    (GPIOPCTL_PMC7_0)|(GPIOPCTL_PMC7_1)|(GPIOPCTL_PMC7_3) );
   GPIOB->PCTL |= ( GPIOPCTL_PMC6_2 | GPIOPCTL_PMC7_2);

 // Enable the GPIO pins (p.682)
    GPIOB->DEN |= (GPIODEN_DEN_6 | GPIODEN_DEN_7);

// Config. Run-Mode Clock Config (RCC p255) reg. to use PWM dvd (USEPWMDIV)
// and set the divider (PWMDIV) to divide by 2 (000).
     SYSCTL->RCC |= RCC_USEPWMDIV;
     SYSCTL->RCC &=~ ( RCC_PWMDIV_0 | RCC_PWMDIV_1 | RCC_PWMDIV_2 );


// Config. PWM generator for countdown with immediate param updates
      // Write the PWM0CTL(p1266 with a value of 0x0000.0000)
    PWM0->_0_CTL = 0x0;
      // Write the PWM0GENA register with a value of 0x0000.008C.
    PWM0->_0_GENA =  \
        (PWMnGENA_ACTLOAD_0 | PWMnGENA_ACTLOAD_1 | PWMnGENA_ACTCMPAD_1);
      // Write the PWM0GENB register with a value of 0x0000.080C.
    PWM0->_0_GENB =  \
         (PWMnGENB_ACTLOAD_0 | PWMnGENB_ACTLOAD_1 | PWMnGENB_ACTCMPBD_1);

// Set the period. For a 25-KHz frequency, the period = 1/25,000, or 40 usec.
// The PWM clock source is 8 MHz (=sys clock div. 2). Thus 500
// ticks per period.  Use this value to set the PWM0LOAD register.
// In Count-Down mode, set the LOAD field in PWM0LOAD to the requested period-1.
//  Write the PWM0LOAD register with a value of [sic.] 0x0000.018F (399)
     PWM0->_0_LOAD = ui32_PWM0LOAD;

//  Set the pulse width of the MnPWM0 pin for a 25% duty cycle.
//  Write the PWM0CMPA register with a value of 0x0000.012B (299)
     PWM0->_0_CMPA =  ui32_PWM0CMPA;

//Set the pulse width of the MnPWM1 pin for a 75% duty cycle.
// Write the PWM0CMPB register with a value of 0x0000.0063 (99)
    PWM0->_0_CMPB = ui32_PWM0CMPB;

// Start the timers in PWM generator 0.
// Write the PWM0CTL register with a value of 0x0000.0001.
    //PWM0->CTL = PWMCTL_GLOBALSYNC0;
    PWM0->_0_CTL = PWMCTL_GLOBALSYNC0;

// Enable PWM outputs.
// Write the PWMENABLE register with a value of 0x0000.0003.
    PWM0->ENABLE = ( PWMENABLE_PWM0EN | PWMENABLE_PWM1EN );


    return;
}

////////////////////////////////////////////////////////////////////////////////
//////////////                fStartPWM() ends                      ////////////
////////////////////////////////////////////////////////////////////////////////



/* todo Approach of supplying a constructor at compile time not yet implemnted
////////////////////////////////////////////////////////////////////////////////
//////////////                fConstructPWMcfg() follows            ////////////
////////////////////////////////////////////////////////////////////////////////
pPWMcfg_t fConstructPWMcfg(                                         \
       uint32_t uint32RCGCGPIO_Rx,                            \
       GPIOA_Type* gpioGPIOx,                                 \
       uint32_t uint32GPIODIR_DIR_x,                          \
       uint32_t uint32GPIOAFSEL_AFSEL_x,                      \
       uint32_t uint32GPIODEN_DEN_x,                          \
       uint32_t uint32GPIOAMSEL_GPIOAMSEL_x   )
{
   static PWMcfg_t strucPWMcfgx; //declare a (static) struc variable...
                                   // ...fill it...
   strucPWMcfgx.RCGCGPIO_Rx           = uint32RCGCGPIO_Rx;
   strucPWMcfgx.GPIOx                 = gpioGPIOx;
   strucPWMcfgx.GPIODIR_DIR_x         = uint32GPIODIR_DIR_x;
   strucPWMcfgx.GPIOAFSEL_AFSEL_x     = uint32GPIOAFSEL_AFSEL_x;
   strucPWMcfgx.GPIODEN_DEN_x         = uint32GPIODEN_DEN_x;
   strucPWMcfgx.GPIOAMSEL_GPIOAMSEL_x = uint32GPIOAMSEL_GPIOAMSEL_x;

   return &strucPWMcfgx;              // ...and return a pointer to it
}
////////////////////////////////////////////////////////////////////////////////
//////////////                fConstructPWM() ends                 ////////////
////////////////////////////////////////////////////////////////////////////////
//void fStartPWM(PWMcfg_t *PWMcfgx)
*/
