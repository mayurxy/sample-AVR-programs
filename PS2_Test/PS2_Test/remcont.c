/*
 * remcont.c
 *
 * Created: 09-01-2013 PM 6:48:38
 *  Author: Ashutosh
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "lcd.h"

int main(void)
{
	int x;
	InitLCD(0);
	LCD(0,0,"START");
	LCDClear();
	DDRC=0x00;
	PORTC=0xFF;
	
	while(1)
    {
		x=PINC;
		_delay_ms(10);
		switch(x)
		{
				case 0b11111110 : LCD(0 , 0 , "1");
						break;
				case 0b11111101 : LCD(0,0, "2");
						break;
				case 0b11111011 : LCD(0 , 0 , "3");
						break;
				case 0b11110111 : LCD(0,0, "4");
						break;
				case 0b11101111 : LCD(0 , 0 , "5");
						break;
				case 0b11011111 : LCD(0,0, "6");
						break;
				case 0b10111111 : LCD(0 , 0 , "7");
						break;
				case 0b01111111 : LCD(0,0, "8");
						break;
    }
        //TODO:: Please write your application code 
    }
}