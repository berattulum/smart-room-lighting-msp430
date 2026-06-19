#include "led.h"

void led_init(void)
{
    P2DIR |= BIT4;
    P2SEL |= BIT4;
    P2SEL2 &= ~BIT4;

    TA1CCR0  = 1000;
    TA1CCTL2 = OUTMOD_7;   
    TA1CCR2  = 0;
    
    TA1CTL = TASSEL_2 + MC_1;
}

void led_set_pwm(unsigned int duty)
{
    if (duty > 1000) duty = 1000;
    TA1CCR2 = duty;   
}
