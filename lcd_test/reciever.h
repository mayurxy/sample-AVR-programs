/*
 * reciever.h
 *
 * Created: 18/01/2014 20:03:51
 *  Author: pranav
 */ 


#ifndef RECIEVER_H_
#define RECIEVER_H_

#include <avr/io.h>
#include "lcd.h"
#include "uart.h"
#include <util/delay.h>
#include <avr/interrupt.h>

volatile unsigned char load=0,mean1[3]={'0','0','0'},mean2[3]={'0','0','0'},ontime1[4]={'0','0','0','0'},ontime2[4]={'0','0','0','0'},ontime3[4]={'0','0','0','0'};
volatile unsigned char pointer0=0,pointer1=0,pointer2=0,ptr1=0,ptr2=0;
volatile int mean_1=0,mean_2=0,ontime_1=0,ontime_2=0,ontime_3=0;
volatile unsigned char string1[5];

ISR(USART1_RX_vect)
{
	

	PORTG=255;
unsigned char temp;
temp=UDR1;     //data register replace this with Uart data register in PIC--RCREG





if (temp=='L')
{
	ptr2=1;
}	


if (temp=='1'&&ptr2==1)
{
ptr2=0;
	load=1;
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

if (temp=='0'&&ptr2==1)
{
ptr2=0;
load=0;
	TCCR1A=0;
				TCCR1B=0;
				TCCR3A=0;
				TCCR3B=0;
				load=0;
				mean_1=0;
				mean_2=0;
				ontime_1=0;
				ontime_2=0;
				ontime_3=0;
}


if(temp=='A')
{
pointer0=0;
}

if(pointer0<4&&temp!='A')
{
ontime1[pointer0]=temp;
pointer0++;
}

if(temp=='B')
{
pointer1=0;
}

if(pointer1<4&&temp!='B')
{
ontime2[pointer1]=temp;
pointer1++;
}

if(temp=='C')
{
pointer2=0;
}

if(pointer2<4&&temp!='C')
{
ontime3[pointer2]=temp;
pointer2++;
}

if(temp=='M')
{
ptr1=0;
}

if(ptr1<6&&temp!='M')
{
	if (ptr1<3)
	{
		mean1[ptr1]=temp;
	}
	else
	mean2[ptr1-3]=temp;
	ptr1++;
}

if (ptr1==6)
{
	mean_1=((mean1[0]-48)*100+(mean1[1]-48)*10+(mean1[2]-48));
	mean_2=((mean2[0]-48)*100+(mean2[1]-48)*10+(mean2[2]-48));
}
if (pointer2==4)
{
	ontime_3=((ontime3[0]-48)*1000+(ontime3[1]-48)*100+(ontime3[2]-48)*10+(ontime3[3]-48));
}
if (pointer1==4)
{
	ontime_2=((ontime2[0]-48)*1000+(ontime2[1]-48)*100+(ontime2[2]-48)*10+(ontime2[3]-48));
}
int on=0;
if (pointer0==4)
{
	on=((ontime1[0]-48)*1000+(ontime1[1]-48)*100+(ontime1[2]-48)*10+(ontime1[3]-48));
if (on<1000 && on>=0)
{

ontime_1=on;
}
}
PORTG=0;
}






#endif /* RECIEVER_H_ */