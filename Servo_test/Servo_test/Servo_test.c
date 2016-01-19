/*
 * Servo_test.c
 *
 * Created: 29-07-2013 18:54:31
 *  Author: Ashutosh
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>



void intialize(void);
void servo(int num , float angle);

void main(void)
{
	DDRE=0xFF;
	//DDRE |= (1<<PE3) | (1<<PE4) | (1<<PE5);
	//int x=63;
	intialize();
	while(1)
    {
	  
	   servo(1,60);
	   _delay_ms(500);
	   servo(1,150);
	   _delay_ms(500);
			  
    }
}
void intialize(void)
{
	
		TCCR3A |=(1<<COM3A1)|(1<<COM3B1)|(1<<COM3C1)|(1<<WGM30) |(0<<COM3A0);  // prescalar 64 //Fast PWM //Clr On Cmp Match
	    TCCR3B |=(1<<WGM32)|(1<<CS30)|(1<<CS31);
}
void servo(int num , float angle)
{
	angle=(angle*(0.090909))+15;
//angle = angle * (0.17777777777778) +31 ;
	
	if (num==1)
	{
		OCR3A = angle;
	}
	
	else if (num==2)
	{
		OCR3B = angle;
	}

	else if (num==3)
	{
		OCR3C = angle;
	}
}
