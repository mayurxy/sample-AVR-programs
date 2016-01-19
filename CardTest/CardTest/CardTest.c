/*
 * CardTest.c
 *
 * Created: 13-01-2013 AM 12:14:15
 *  Author: Ashutosh
 */ 


#include <avr/io.h>
#define F_CPU 16000000
#include "lcd.h"
#include <util/delay.h>
#include "MyDefs.h"

void init_t0()
{
	TCCR0=(1<<COM01)|(1<<WGM00)|(1<<WGM01)|(1<<CS01); // prescalar 8
	OCR0=0;
	TCNT0=0;
}

void init_t3()
{
	
	TCCR3A = (1<<WGM30) | (0<<WGM31) | (1<<WGM32)|(1 << COM3A1) |(1 << COM3B1) |(1 << COM3C1); // fast pwm mode
	TCCR3B	= (1<<CS02) | (0<<CS01) | (0<<CS00); //prescalers of 8
		
}
void init_t1()
{
	TCCR1A	= 	(1<<WGM10) | (0<<WGM11) | (1<<WGM12)|(1 << COM1A1) |(1 << COM1B1) |(1 << COM1C1);
	TCCR1B	= (1<<CS02) | (0<<CS01) | (0<<CS00); //prescalers of 8
}




int main(void)
{
	InitLCD(0);
	LCD(0,0,"HELLO");
	while(1);
	_delay_ms(500);
	LCDClear();
	
	init_t0();
	_delay_ms(1000);
	init_t1();
	_delay_ms(1000);
	init_t3();
	_delay_ms(1000);
	DDRA=255;
	DDRB=255;
	//DDRC=255;
//	DDRD=255;
	DDRE=255;
	DDRF=255;
	
	while(1)
    {
		
		PORTA =255 ;
	//	PORTC =255 ;
		PORTD =255 ;
		PORTE =255 ;
		PORTF =255 ;
		glow1();
		glow2();
		glow3();
		glow4();
		_delay_ms(1000);
		off1();
		off2();
		off3();
		off4();
		PORTA = 0;
	//	PORTC =0;
		PORTD =0 ;
		PORTE = 0;
		PORTF = 0;
		_delay_ms(1000);
		/*
		OCR0 = 200;
		_delay_ms(1000);
		_delay_ms(1000);
		LCDvar(0,0,OCR0 , 3);
		_delay_ms(1000);
		OCR1A  = 12200;
		OCR1B  = 12200;
		OCR1C  = 12200;
		_delay_ms(1000);
		_delay_ms(1000);
		LCDvar(4,0,OCR1A , 3);
		LCDvar(8,0,OCR1B,3);
		LCDvar(12,0,OCR1C,3);
		_delay_ms(1000);
		OCR3A = 12240 ; 
		OCR3B=12240;
		OCR3C=12240;
		_delay_ms(1000);
		_delay_ms(1000);
		LCDvar(0,1,OCR3A , 3);
		LCDvar(4,1,OCR3B,3);
		LCDvar(8,1,OCR3C,3);
		_delay_ms(1000);
		/////////2nd //////////
		OCR0 = 50;
		_delay_ms(1000);
		_delay_ms(1000);
		LCDvar(0,0,OCR0 , 3);
		_delay_ms(1000);
		OCR1A  = 7000;
		OCR1B  = 7000;
		OCR1C  = 7000;
		_delay_ms(1000);
		_delay_ms(1000);
		LCDvar(4,0,OCR1A , 3);
		LCDvar(8,0,OCR1B,3);
		LCDvar(12,0,OCR1C,3);
		_delay_ms(1000);
		OCR3A = 7000 ;
		 
		OCR3B=7000;
		OCR3C=7000; 
		_delay_ms(1000);
		_delay_ms(1000);
		LCDvar(0,1,OCR3A , 3);
		LCDvar(4,1,OCR3B,3);
		LCDvar(8,1,OCR3C,3);
		_delay_ms(1000);*/
	}
}

