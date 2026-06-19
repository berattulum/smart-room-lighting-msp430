#ifndef LED_H
#define LED_H

#include <msp430.h>

void led_init(void);
void led_set_pwm(unsigned int duty);

#endif