/*
 * Ultra_Test.c
 *
 * Created: 13-01-2013 AM 3:50:06
 *  Author: Ashutosh
 */ 

#include <avr/io.h>
#include "lcd.h"
#include "mydefs.h"
#include "wall.h"
#include <util/delay.h>

int main(void)
{
	int x;
	InitLCD(0);
	LCDClear();
	
	ultrainit_timer3();
    while(1)
    {
		x=distance3_new(1);
		LCDvar(1, 1 ,  x , 5);
		_delay_ms(100);
	}
}