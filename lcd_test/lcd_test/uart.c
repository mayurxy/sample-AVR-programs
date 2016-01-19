

#include<avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

#include "mydefs.h"

unsigned char USART1_Recieve()
{
while(!(UCSR1A & (1<<RXC1)));
return UDR1;
}
void uart_0_ini()
{
UCSR0B=((1<<RXEN0)|(1<<RXCIE0));
UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);
UBRR0L=103;
UBRR0H=0;
DDRE|=(1<<1);
DDRE&=~(1<<0);
}
void uart_1_ini()
{
	
UCSR1B=((1<<RXEN1)|(1<<TXEN1));
UCSR1C=((1<<UCSZ11)|(1<<UCSZ10));
UBRR1L=103;
UBRR1H=0;
set(DDRD,3);
clr(DDRD,2);

}
void uart_0_Transmit(unsigned char data)
{
while(!(UCSR0A&(1<<UDRE0)));
UDR0=data;
}

void uart_1_Transmit(unsigned char data)
{
while(!(UCSR1A&(1<<UDRE1)));
UDR1=data;
}

void stringuart0( char*string)
{
	while(*string)
	uart_0_Transmit(*string++);
}

void stringuart1(char*string)
{
	while(*string)
	uart_1_Transmit(*string++);
}

void uartWriteInt(int val,unsigned int field_length)
{
	

	char str[5]={0,0,0,0,0};
	int i=4,j=0;
	if(val<0) 
	{
	uart_1_Transmit('-');
	val=val*(-1);
	}	
	else
	uart_1_Transmit('+');
	while(val)
	{
	str[i]=val%10;
	val=val/10;
	i--;
	}
	if(field_length==-1)
		while(str[j]==0) j++;
	else
		j=5-field_length;

	
	for(i=j;i<5;i++)
	{
	uart_1_Transmit(48+str[i]);
	}
}
