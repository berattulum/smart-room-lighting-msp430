#ifndef LDR_H
#define LDR_H

#include <msp430.h>

#define KARANLIK_ESIK  500    // test sonrası ayarlayacaksın

void ldr_init(void);
unsigned int ldr_oku(void);

#endif
