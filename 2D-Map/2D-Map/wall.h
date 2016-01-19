#include <avr/io.h>
#ifndef F_CPU
	#define F_CPU 16000000UL
#endif
#include <util/delay.h>
#include "motors.h"
#include "encoder_maxon.h"


void ultrainit_t2() // ultrasonic pulse time counter
{
TCCR2=(1<<CS22);

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

uint16_t distance(int n)
{
	uint16_t temp;
	set(DDRF,n);
	clr(DDRF,n+1);
		
	set(PORTF,n);
	_delay_us(15);
	clr(PORTF,n);
	
	while(!(PINF&1<<(n+1)))
		{
		
		}
	TCNT2=0;
	
	while((PINF&1<<(n+1)))
	{
		if(TCNT2>250)
		break;
	}
	temp=TCNT2;

		temp=temp;
			
	return temp;		
}
uint16_t distance3_new(int n)
{	
	uint16_t temp,i=600000;
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
	i=0xffff;	
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
	char n=0;
	if(no==1||no==2)
	{
		if(no==1)
		n=6;
		else
		n=7;
//	off1();
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
	                                                                                                                                                                                                                            
	i=60000;	
	while(chk(PINA,n)&&(i!=0))
	{
		i--;
		if(TCNT2>250)
		break;
	}
	temp=TCNT2;
	if(i==0)
		return 0xff;
	//temp=(temp*1.1);
	//off2();
	return temp;
	}
	else
	{
		if(no==3)
		n=6;
		else
		n=7;
	
	//glow1();
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
	
	i=60000;	
	while(chk(PINF,n)&&(i!=0))
	{
		i--;
		if(TCNT2>250)
		break;
	}
	temp=TCNT2;
	if(i==0)
		return 0xff;
	//temp=(temp*1.1);
	//off2();
	return temp;
	}
}	



void straight(uint16_t enco_dist,uint8_t speed_1,uint8_t speed_2,uint8_t s_diff,uint8_t ideal_dist)
{
uint8_t bot_status=0x00,diff,dist1,dist2;
      while(maxon1<enco_dist)
{	dist1=distance_8ui(1);
	dist2=distance_8ui(2);
	bot_status=0x00;    
		diff=0;
		
		//////////////////////////////////////////////////
		
		if(dist1>dist2)
		{
			
			diff=dist1-dist2;
			if(diff>=1)
			bot_status=0b00000010;		//right
		}
		else if(dist1<dist2)
		{
			
			diff=dist2-dist1;
			if(diff>=1)
			bot_status=0b00000001;		//left
		}
		
		LCDvar(10,1,diff,3)
		//////////////////////////////////////////////////
		
		if(diff>=1&&diff<4)
			bot_status|=0b00000100;
		
		else if(diff>=4&&diff<10)
			bot_status|=0b00001100;
		
		else if(diff>=10&&diff<18)
			bot_status|=0b00011100;
			
		else if(diff>=18)
			bot_status|=0b00111100;
		
		/////////////////////////////////////////////////
		
		if (ideal_dist+5<dist1)
			{
				bot_status=0b10000000;
			}			
		if (ideal_dist-5>dist1)
			{
				bot_status=0b01000000;
			}
					
		////////////////////////////////////////////////
		
		switch (bot_status)
			{	
				case 0b00000000:drive_lr(speed_1,speed_2);
								break;	
				
				case 0b10000000:drive_lr(speed_1,speed_2-s_diff*2);
								break;
				case 0b01000000:drive_lr(speed_1-s_diff*2,speed_2);
								break;

				case 0b00000110:drive_lr(speed_1,speed_2);
								break;
				case 0b00000101:drive_lr(speed_1,speed_2);
								break;
				
				case 0b00001110:drive_lr(speed_1,speed_2-s_diff*2);
								break;
				case 0b00001101:drive_lr(speed_1-s_diff*2,speed_2);
								break;

				case 0b00011110:drive_lr(speed_1,speed_2-s_diff*4);
								break;
				case 0b00011101:drive_lr(speed_1-s_diff*4,speed_2);
								break;
			
				case 0b00111110:drive_lr(120,50);
								break;
				case 0b00111101:drive_lr(50,120);
								break;
/*				
				case 0b00111110:drive_lr(120,0);
								break;
				case 0b00111101:drive_lr(0,120);
								break;
				
*/			
			}
			}
				
}



void adjust()
{
	uint16_t dist1,dist2,diff=0;
			
			dist1=distance_8ui(1);
			
			dist2=distance_8ui(2);
				
	
			do
			{
				if(dist1>dist2)
				{
				drive_lr(0,-80);
				}
				if(dist1<dist2)
				{
				drive_lr(0,80);
				}
				
								
				dist1=distance_8ui(1);
			
				dist2=distance_8ui(2);
				
				if(dist1>dist2)
				{
				diff=dist1-dist2;
				}			
				else if(dist1<dist2)
				{
				diff=dist2-dist1;
				}
				
			}
			while(diff>2);
			
}



uint16_t distance2_new(int n)
{	
	uint16_t temp,i=600000;
	DDRA=1<<n;
	PORTA=1<<n;
	_delay_us(15);
	PORTA=0;
	_delay_us(20);
	DDRA=0;
	while((!(PINA&1<<n))&&i!=0)
		{
		i--;	
		}
	TCNT1=0;
	if(i==0)
		return 0xffff;
	i=0xffff;	
	while((PINA&1<<n)&&(i!=0))
	{
		i--;
	}
	temp=TCNT1;
	if(i==0)
		return 0xffff;
	temp=(temp/(58*2)+3);
	
	
	if (n==1)
		{LCDvar(0,0,temp,3);} 
	else
		{LCDvar(4,0,temp,3);}
	return temp;

}
