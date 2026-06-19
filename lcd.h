#ifndef LCD_H
#define LCD_H

#include <msp430.h>

#define LCD_ADRES  0x27
#define LCD_SATIR1 0x80
#define LCD_SATIR2 0xC0

void lcd_init(void);
void lcd_temizle(void);
void lcd_konumlan(unsigned char satir, unsigned char sutun);
void lcd_yaz(char *str);
void lcd_yaz_sayi(int sayi); //EN SON EKLENEN

#endif