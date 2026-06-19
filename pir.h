#ifndef PIR_H
#define PIR_H

#include <msp430.h>

extern volatile unsigned int hareket_var;

void pir_init(void);

#endif
