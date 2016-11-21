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

#ifndef TM4C_UTILS_FPU_HELPER_H_
#define TM4C_UTILS_FPU_HELPER_H_

#define CPAC               (*((volatile uint32_t *)(0xE000ED88)))  // Coprocessor Access Control
#define FPCC   			   (*((volatile uint32_t *)(0xE000EF34)))

void FPU_Start(void);

#endif /* TM4C_UTILS_FPU_HELPER_H_ */
