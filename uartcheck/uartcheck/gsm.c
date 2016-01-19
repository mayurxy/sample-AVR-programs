/*
 * gsm.c
 *
 * Created: 1/1/2013 7:33:25 PM
 *  Author: Pranav
 */ 

#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>

#ifndef F_CPU
	#define F_CPU 8000000UL
#endif

#include <util/delay.h>

#include "lcd.h"
#include "uart.h"
#include "gsm.h"
unsigned char checkok()
{
	
	LCD(0,0,"inok");
	unsigned char reply[2]={'0','0'};
	while(USART1_Recieve()!='O');
	LCD(0,0,"loopkhatam");
	reply[0]='O';
	LCD(0,0,"orecived");
	reply[1]=USART1_Recieve();
	LCD(0,0,"receive");
	LCDGotoXY(0,1);
	LCDData(reply[0]);
	LCDData(reply[1]);
	
	if (reply[0]=='O'&&reply[1]=='K')
	{
		return 1; 
	}
	else
	return 0;
}

unsigned char sms(unsigned char *num,unsigned char *msg)
{
	stringuart1("AT");
	uart_1_Transmit('+');
	stringuart1("CMGF");
	uart_1_Transmit('=');
	uart_1_Transmit('1');
	uart_1_Transmit(13);
	if (checkok()==1)
	{
	stringuart1("AT+CMGS=");
	uart_1_Transmit('"');
			
	while(*num)
	uart_1_Transmit(*num++);
	
	uart_1_Transmit('"');
	uart_1_Transmit(13);
	while(USART1_Recieve()!='>');
	
	
			while(*msg)
			uart_1_Transmit(*msg++);
			uart_1_Transmit(26);
	}	
	
	else
	{
	return 0;
	}
}




unsigned char call(unsigned char *number)
{
	stringuart1("ATD");
	
			
	while(*number)
	uart_1_Transmit(*number++);
	uart_1_Transmit(';');
	uart_1_Transmit(13);
	LCD(0,0,"Dialling");
	_delay_ms(10);
	if (checkok()==1)
	{
		return 1;
	}
	else
	return 0;
}


