#include <msp430.h>
#include "ldr.h"
#include "pir.h"
#include "led.h"
#include "lcd.h"
#include "bluetooth.h"

volatile unsigned int ldr_degeri = 0;
volatile unsigned int pwm_hedef_degeri = 0;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    // Clock kalibrasyonu — lcd.c içinde de var ama burada da olsun
    if (CALBC1_1MHZ == 0xFF) while(1);
    DCOCTL  = 0;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;

    ldr_init();
    pir_init();
    led_init();
    __enable_interrupt();
    lcd_init();
    bluetooth_init();

    while(1)
    {
        ldr_degeri = ldr_oku();

        if (hareket_var == 1)
        {
            if (ldr_degeri < KARANLIK_ESIK)
            {
                pwm_hedef_degeri = (unsigned int)((long)(KARANLIK_ESIK - ldr_degeri) * 1000 / KARANLIK_ESIK);
                led_set_pwm(pwm_hedef_degeri);
            }
            else
            {
                led_set_pwm(0);
            }
        }
        else
        {
            led_set_pwm(0);
        }

        lcd_konumlan(0, 0);
        lcd_yaz("LDR: ");
        lcd_yaz_sayi(ldr_degeri);
        lcd_yaz("    ");

        lcd_konumlan(1, 0);
        if (hareket_var && ldr_degeri < KARANLIK_ESIK)
           lcd_yaz("LED: ACIK      ");
        else
            lcd_yaz("LED: KAPALI    ");

        bluetooth_yaz("LDR:");
        bluetooth_yaz_sayi(ldr_degeri);
        bluetooth_yaz(" ");
    
        if (hareket_var && ldr_degeri < KARANLIK_ESIK)
            bluetooth_yaz("LED:ACIK\r\n");
        else
            bluetooth_yaz("LED:KAPALI\r\n");

        __delay_cycles(100000);
    }

    return 0;
}