/*
 * PS2_Test.c
 *
 * Created: 17-01-2013 PM 8:04:07
 *  Author: Ashutosh
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

unsigned int ADC_analog(unsigned char channel)
{
ADCSRA|=((1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));
ADMUX=channel;
set(ADCSRA,ADSC);

while(chk(ADCSRA,ADSC));
glow1();
return(ADC);

}

void enable_ps2()
	{
	DDRF=0x00;
	PORTF=0x55;
	DDRD=0x00;
	PORTD=0xFF;
	}

int main(void)
{
	init_t0();
	init_t1();
	InitLCD(0);
	LCD(0, 0 , "HELLO");
	_delay_ms(500);
	LCDClear();
	enable_ps2();
	
   
}