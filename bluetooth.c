#include "bluetooth.h"

void bluetooth_init(void)
{
    P1SEL  |= BIT1 + BIT2;
    P1SEL2 |= BIT1 + BIT2;

    UCA0CTL1 |= UCSSEL_2;    // SMCLK
    UCA0BR0   = 104;          // 1MHz / 9600 baud
    UCA0BR1   = 0;
    UCA0MCTL  = UCBRS_1;
    UCA0CTL1 &= ~UCSWRST;    
}

static void bt_char_gonder(char c)
{
    while (!(IFG2 & UCA0TXIFG));
    UCA0TXBUF = c;
}

void bluetooth_yaz(char *str)
{
    while (*str)
        bt_char_gonder(*str++);
}

void bluetooth_yaz_sayi(int sayi)
{
    char tampon[6];
    int i = 0;
    if (sayi == 0) { bt_char_gonder('0'); return; }
    while (sayi > 0) {
        tampon[i++] = '0' + (sayi % 10);
        sayi /= 10;
    }
    int j;
    for (j = i - 1; j >= 0; j--)
        bt_char_gonder(tampon[j]);
}