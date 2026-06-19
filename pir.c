#include "pir.h"


volatile unsigned int hareket_var = 0; 

void pir_init(void)
{
    
    P2DIR &= ~BIT0;    
    P2REN |= BIT0;    
    P2OUT &= ~BIT0;    

    
    P2IE |= BIT0;      
    P2IES &= ~BIT0;    
    P2IFG &= ~BIT0;    
}


#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    
    if (P2IFG & BIT0) 
    {
        if (P2IES & BIT0) 
        {
            
            hareket_var = 0;
            P2IES &= ~BIT0; 
        }
        else 
        {
            
            hareket_var = 1;
            P2IES |= BIT0;  
        }

        
        P2IFG &= ~BIT0; 
    }
}
