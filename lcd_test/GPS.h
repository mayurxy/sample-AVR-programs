/*
 * GPS.h
 *
 * Created: 1/1/2013 2:41:18 PM
 *  Author: Pranav
 */ 


#ifndef GPS_H_
#define GPS_H_

#include <avr/io.h>
#include "lcd.h"
#include "uart.h"
#include <util/delay.h>
#include <avr/interrupt.h>

volatile unsigned char lati[11]={'0','0','0','0','0','0','0','0','0','0','0'},longi[12]={'0','0','0','0','0','0','0','0','0','0','0','0'},time[9]={'0','0','0','0','0','0','0','0','0'},date[6]={'0','0','0','0','0','0'},speed[5]={'0','0','0','0','0'},valid='N',latdir='0',longdir='0';
volatile unsigned char pointer=0,latptr=0,longptr=0,timeptr=0,dateptr=0,speedptr=0,ptr=0;

volatile unsigned char string1[5];

ISR(USART0_RX_vect)
{
	
	PORTG=255;
unsigned char temp;
temp=UDR0;     //data register replace this with Uart data register in PIC--RCREG



if(temp=='$')
{
pointer=0;
latptr=0;longptr=0;timeptr=0;dateptr=0;speedptr=0;ptr=0;
}
if(pointer<5&&temp!='$')
{
string1[pointer]=temp;
pointer++;
}
if (string1[0]=='G'&&string1[1]=='P'&&string1[2]=='R'&&string1[3]=='M'&&string1[4]=='C'&&pointer>4)
{
	if (temp==',')
	{
		ptr++;
	}
	if(ptr==1&&temp!=',')
	{
		time[timeptr]=temp;
		timeptr++;
	}
	else if(ptr==2&&temp!=',')
	{
		valid=temp;
	}
	else if(ptr==3&&temp!=',')
	{
		lati[latptr]=temp;
		latptr++;
	}
	else if(ptr==4&&temp!=',')
	{
		latdir=temp;
	}
	else if(ptr==5&&temp!=',')
	{
		longi[longptr]=temp;
		longptr++;
	}
	else if(ptr==6&&temp!=',')
	{
		longdir=temp;
	}
	else if(ptr==7&&temp!=',')
	{
		speed[speedptr]=temp;
		speedptr++;
	}
	else if(ptr==8&&temp!=',')
	{
		
	}
	else if (ptr==9&&temp!=',')
	{
		date[dateptr]=temp;
	dateptr++;
	}
	
}




PORTG=0;

}


#endif /* GPS_H_ */