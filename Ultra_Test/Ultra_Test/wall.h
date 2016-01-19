#include <avr/io.h>
#ifndef F_CPU
	#define F_CPU 16000000UL
#endif
#include <util/delay.h>

void ultrainit_t2() // ultrasonic pulse time counter
{
TCCR2=(1<<CS20)|(1<<CS22);
}

void ultrainit_timer3()
{
	//TCCR2=0;
	//clr(TIMSK,OCIE2);
	TCCR3A=0;
	clr(ETIMSK,OCIE3A);
	TCCR3B=(1<<CS31)|(1<<CS30);
	TCNT3=0;
//TCCR2=(1<<CS22);//|(1<<CS20);
//TCNT2=0;
}


uint16_t distance3_new(int n)
{	
	uint16_t temp,i=6000;
	DDRF=1<<n;
	PORTF=1<<n;
	_delay_us(15);
	PORTF=0;
	_delay_us(20);
	DDRF=0;
	while((!(PINF&1<<n))&&i!=0)
		{
		i--;	
		}
	TCNT3=0;
	if(i==0)
		return 0xffff;
	i=6000;	
	while((PINF&1<<n)&&(i!=0))
		{
		i--;
		if(TCNT3>1000)
		break;
	}
	temp=TCNT3;
	if(i==0)
		return 0xffff;
	return temp;
	
	
}

uint8_t distance_8ui(int no) // no: 1=PA6	2=PA7	3=PF6	4=PF7
{	
	char n;
	if(no==1||no==2)
	{
		if (no==1);
		n=6;
		if (no==2);
		n=7;
	uint8_t temp;
	uint16_t i=60000;
	set(DDRA,n);
	set(PORTA,n);
	_delay_us(15);
	clr(PORTA,n);
	_delay_us(20);
	clr(DDRA,n);
	while((!(chk(PINA,n)))&&(i!=0))
		{
		i--;	
		}
	TCNT2=0;
	if(i==0)
		return 0xff;
	i=0xffff;	
	while(chk(PINA,n)&&(i!=0))
	{
		i--;
	}
	temp=TCNT2;
	if(i==0)
		return 0xff;
	temp=(temp*1.1);
	
	return temp;
	}
	else if(no==3||no==4)
	{
		if (no==3);
		n=6;
		if (no==4);
		n=7;
	uint8_t temp;
	uint16_t i=60000;
	set(DDRF,n);
	set(PORTF,n);
	_delay_us(15);
	clr(PORTF,n);
	_delay_us(20);
	clr(DDRF,n);
	while((!(chk(PINF,n)))&&(i!=0))
		{
		i--;	
		}
	TCNT2=0;
	if(i==0)
		return 0xff;
	i=0xffff;	
	while(chk(PINF,n)&&(i!=0))
	{
		i--;
	}
	temp=TCNT2;
	if(i==0)
		return 0xff;
	temp=(temp*1.1);
	
	return temp;
	
	}	
}
 



