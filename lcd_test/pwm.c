/*
 * pwm.c
 *
 * Created: 05/09/2013 13:33:48
 *  Author: pranav
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>
//#include "pwm.h"


volatile  char front=0,back=0,left=0,right=0;


void init_timer()
{
	DDRB|=0xF0;
	DDRE|=(1<<5);
	//TCCR0=(1<<COM01)|(1<<WGM00)|(1<<WGM01)|(1<<CS00)|(1<<CS02)|(1<<CS01); // prescalar 8
	//OCR0=16;
	//TCNT0=0;
	
	TCCR1A=(1<<COM1A1)|(1<<COM1B1)|(1<<COM1C1)|(1<<WGM11);  // prescalar 8
	TCCR1B=(1<<WGM12)|(1<<WGM13)|(1<<CS11);
	ICR1=40000;
	OCR1A=2000;
	OCR1B=2000;
	OCR1C=2000;
	
	TCCR3A=(1<<COM1A1)|(1<<COM1B1)|(1<<COM1C1)|(1<<WGM11);  // prescalar 8
	TCCR3B=(1<<WGM12)|(1<<WGM13)|(1<<CS11);
	ICR3=40000;
	OCR3A=0;
	OCR3B=0;
	OCR3C=2000;
	
}

void setspeed(int motornum,int speedinput)
{

	if (motornum==3)
	{
		OCR1A=2000+(2*speedinput);
	}
	else if (motornum==2)
	{
		OCR1B=2000+(2*speedinput);
	}
	else if (motornum==1)
	{
		OCR1C=2000+(2*speedinput);
	}
	else if (motornum==4)
	{
		OCR3C=2000+(2*speedinput);
		//OCR0=(float)15.625+(0.156
		//25*((float)speedinput));//31.25
	}
}


