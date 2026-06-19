#include "ldr.h"

void ldr_init(void)
{
    ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON;  
    ADC10CTL1 = INCH_0;                           
    ADC10AE0  = BIT0;                             
}

unsigned int ldr_oku(void)
{
    ADC10CTL0 |= ENC + ADC10SC;       
    while (ADC10CTL1 & ADC10BUSY);    
    return ADC10MEM;                  
}