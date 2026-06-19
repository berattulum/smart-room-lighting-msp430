#include "lcd.h"
#include <msp430.h>

#define LCD_ADRES 0x27

static void i2c_bus_kurtar(void) {
    volatile int i;
    P1SEL  &= ~(BIT6 | BIT7); 
    P1SEL2 &= ~(BIT6 | BIT7);
    P1DIR  |= BIT6;
    P1OUT  |= BIT6;           
    for(i = 0; i < 9; i++) {
        P1OUT &= ~BIT6;
        __delay_cycles(100);
        P1OUT |= BIT6;
        __delay_cycles(100);
    }
}

static void i2c_init(void) {
    i2c_bus_kurtar();

    P1SEL  |= BIT6 | BIT7;
    P1SEL2 |= BIT6 | BIT7;

    UCB0CTL1 |= UCSWRST;
    UCB0CTL0  = UCMST | UCMODE_3 | UCSYNC;
    UCB0CTL1  = UCSSEL_2 | UCSWRST;
    UCB0BR0   = 10;
    UCB0BR1   = 0;
    UCB0I2CSA = LCD_ADRES;
    UCB0CTL1 &= ~UCSWRST;
}

static void i2c_yaz(unsigned char veri) {
    while (UCB0CTL1 & UCTXSTP);
    UCB0CTL1 |= UCTR | UCTXSTT;
    while (!(IFG2 & UCB0TXIFG));
    if (UCB0STAT & UCNACKIFG) {
        UCB0CTL1 |= UCTXSTP;
        while (UCB0CTL1 & UCTXSTP);
        return;
    }
    UCB0TXBUF = veri;
    while (!(IFG2 & UCB0TXIFG));
    UCB0CTL1 |= UCTXSTP;
    while (UCB0CTL1 & UCTXSTP);
}

static void lcd_tetikle(unsigned char veri) {
    i2c_yaz(veri | 0x0C);
    __delay_cycles(1000);
    i2c_yaz(veri | 0x08);
    __delay_cycles(1000);
}

static void lcd_komut(unsigned char komut) {
    lcd_tetikle(komut & 0xF0);
    lcd_tetikle((komut << 4) & 0xF0);
    __delay_cycles(2000);
}

static void lcd_karakter(unsigned char c) {
    lcd_tetikle((c & 0xF0) | 0x01);
    lcd_tetikle(((c << 4) & 0xF0) | 0x01);
}

void lcd_init(void) {
    i2c_init();
    __delay_cycles(100000);
    lcd_tetikle(0x30); __delay_cycles(10000);
    lcd_tetikle(0x30); __delay_cycles(2000);
    lcd_tetikle(0x30); __delay_cycles(2000);
    lcd_tetikle(0x20);
    lcd_komut(0x28);
    lcd_komut(0x0C);
    lcd_komut(0x01);
    __delay_cycles(20000);
}

void lcd_temizle(void) {
    lcd_komut(0x01);
    __delay_cycles(20000);
}

void lcd_konumlan(unsigned char satir, unsigned char sutun) {
    lcd_komut((satir == 0 ? LCD_SATIR1 : LCD_SATIR2) + sutun);
}

void lcd_yaz(char *str) {
    while (*str)
        lcd_karakter((unsigned char)*str++);
}

void lcd_yaz_sayi(int sayi) {
    char tampon[6];
    int i = 0;
    int gecici = sayi;
    if (sayi == 0) { lcd_karakter('0'); return; }
    while (gecici > 0) {
        tampon[i++] = '0' + (gecici % 10);
        gecici /= 10;
    }
    int j;
    for (j = i - 1; j >= 0; j--)
        lcd_karakter(tampon[j]);
}