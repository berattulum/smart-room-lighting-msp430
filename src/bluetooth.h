#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <msp430.h>

void bluetooth_init(void);
void bluetooth_yaz(char *str);
void bluetooth_yaz_sayi(int sayi);

#endif