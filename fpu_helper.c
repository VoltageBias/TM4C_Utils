////////////////////////////////////////////////////////////////////////////////
//
// VoltageBias - the Blog.
// Author: Gilbert Waltoon
//
// Released under a GNU General Public License v3.0
//
// FILENAME : fpu_helper.c
// PURPOSE  : A set of helper functions to operate the TM4C123 ADC
//
// Version 0: Nov 21, 2016
//
////////////////////////////////////////////////////////////////////////////////
#include "fpu_helper.h"
#include "TM4C123GH6PM.h"
#include "tm4c_register_fields.h"

void FPU_Start(void){

// Enable lazy stacking
	FPCC &=~ (FPCC_LSPEN | FPCC_ASPEN);


// Coprocessor Access Privilege
// Data sheet p.134 explains that the following assembler-code enables the FPU:
//
//	; CPACR is located at address 0xE000ED88
//	LDR.W R0, =0xE000ED88
//	; Read CPACR
//	LDR R1, [R0]
//	; Set bits 20-23 to enable CP10 and CP11 coprocessors
//	ORR R1, R1, #(0xF << 20)
//	; Write back the modified value to the CPACR
//	STR R1, [R0]; wait for store to complete
//	DSB
//	;reset pipeline now the FPU is enabled
//	ISB

//  This is essentially the same as the following assembler, which is in turn
//  the dissamemly of the next line of C-code
//	               ldr        r2, [pc, #0x18]
//	               ldr        r3, [pc, #0x18]
//	               ldr        r3, [r3]
//	         	   orr        r3, r3, #0xf00000
//	               str        r3, [r2]

	CPAC |= (CPAC_CP10_0 | CPAC_CP10_1 | CPAC_CP11_0 |CPAC_CP11_1);

	return;
}
