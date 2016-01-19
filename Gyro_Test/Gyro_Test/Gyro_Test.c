/*
 * Gyro_Test.c
 *
 * Created: 15-02-2013 17:50:17
 *  Author: Ashutosh
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "lcd.h"
#include "gyro.h"


int main(void)
{
	int temp;
    InitLCD(0);
	_delay_ms(10);
	LCD(0,0, "HELLO");
	_delay_ms(500);
	LCDClear();
	_delay_ms(10);
	TWI_init_master();
	sei();
	while(1)
    {
	      LCDvar(1,1 , Z_angle , 5);
    }
}