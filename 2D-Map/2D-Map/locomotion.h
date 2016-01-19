/*
 * locomotion.h
 *
 * Created: 8/28/2012 9:07:31 AM
 *  Author: PRANAV
 */ 


#ifndef LOCOMOTION_H_
#define LOCOMOTION_H_

#include <avr/io.h>
#ifndef F_CPU
	#define F_CPU 16000000UL
#endif

#include <util/delay.h>

#include <avr/interrupt.h>

#include "lcd.h"
#include "mydefs.h"
#include "motors.h"
#include "gyro.h"
#include "encoder_maxon.h"
#include "globalvariables.h"

#define rightturn 0
#define leftturn 1
#define onspot 1
#define curve 0
extern volatile float X_angle,Y_angle,Z_angle;
extern volatile unsigned char task=0;
extern volatile unsigned int maxon1;

uint16_t var=0;
volatile uint8_t pick=1,predist,maxtemp=0;

volatile unsigned char count1=0,count2=0;



void enable_int2()
{
clr(EICRA,ISC21);
//clr(EICRA,ISC20);
EIMSK|=(1<<INT2);
clr(DDRD,2);
}

void enable_int3()
{
EICRA|=(1<<ISC31);
EIMSK|=(1<<INT3);
clr(DDRD,3);
}


void enable_int4()
{
clr(EICRB,ISC41);
//clr(EICRB,ISC40);
EIMSK|=(1<<INT4);
clr(DDRE,4);
}

void enable_int5()
{
clr(EICRB,ISC51);
EIMSK|=(1<<INT5);
clr(DDRE,5);
}

void enable_int7()
{
EICRB|=(1<<ISC71);
EIMSK|=(1<<INT7);
clr(DDRE,7);
}


void enable_interrupts()
{
 enable_int2();
// enable_int3();
 enable_int4();
 enable_int5();
// enable_int7();
}


void disable_int4()
{
EIMSK&=~(1<<INT4);
}

void disable_int3()
{
EIMSK&=~(1<<INT3);
}

void disable_int5()
{
EIMSK&=~(1<<INT5);
}

void disable_int2()
{
EIMSK&=~(1<<INT2);
}

void disable_int7()
{
EIMSK&=~(1<<INT7);
}


void disable_interrupts()
{
 disable_int4();
 disable_int5();
 disable_int2();
 disable_int3();
 disable_int7();
}
void gradual_turn(int side,int angle)
{
	Z_angle=0;
	
	if(side==rightturn)//right
	{
		Z_angle=0;
		while(Z_angle>(-4))
	{
	
	
		drive_fb(30,30);
		drive_lr(15,-15);
	
	}
	while(Z_angle>(-10))
	{
	
	
		drive_fb(60,60);
		drive_lr(20,-20);
	
	}
	while(Z_angle>(-(angle)))
	{
		
	
	
		drive_fb(90,90);
		drive_lr(20,-20);
	
	}	
	//drive_fb(0,0);
	drive_lr(0,0);
	}
	else if(side==leftturn)	
	{
		Z_angle=0;
		while(Z_angle<(4))
		{
		
				drive_fb(30,30);
				drive_lr(-15,15);
		}
		while(Z_angle<(10))
		{
		
				drive_fb(60,60);
				drive_lr(-20,20);
		}while(Z_angle<((angle)))
		{
		
				drive_fb(90,90);
				drive_lr(-20,20);
		}	
	
	//drive_fb(0,0);
	drive_lr(0,0);
	}	
		
	
	Z_angle=0;
}
void bot_turn(int side,int angle,int mode)
{
	
	
	Z_angle=0;
	
	if(side==rightturn)//right
	{
		Z_angle=0;
		
	while(Z_angle>(-(angle)))
	{
	LCDvar(0,0,Z_angle,3);
		if(mode==onspot)
		{
		drive_fb(70,-70);
		drive_lr(70,-70);
		}
		else if(mode==curve)
		{
		drive_fb(80,0);	
		}			
	
	}	
	drive_fb(0,0);
	drive_lr(0,0);
	}
	else if(side==leftturn)	
	{
		Z_angle=0;
		while(Z_angle<((angle)))
		{
		LCDvar(0,0,Z_angle,3);
			if(mode==onspot)
			{
				drive_fb(-70,70);
				drive_lr(-70,70);
			}
			else if(mode==curve)
			{
				drive_fb(0,80);
			}			
		}	
	
	drive_fb(0,0);
	drive_lr(0,0);
	}	
		
	
	Z_angle=0;
}

void sidha(int dist,int ls,int rs,int dif)
{ 
	//proxy F0-left,F1-right
	
	char status;

		while(maxon1<dist)
		{   
			status=0;
//			_delay_ms(100);
        drive_lr(0,0);	 
		LCDvar(0,0,maxon1,4);
		LCDvar(0,1,Z_angle,5);
		if(Z_angle<-1)
		status|=0b00000001;  //left turn
		else if(Z_angle>1)
		status|=0b00000010;  //right turn
		///////////////////////
		if((Z_angle>1&&Z_angle<3)||(Z_angle<-1&&Z_angle>-3))
		status|=0b00000100;
		if((Z_angle>3&&Z_angle<40)||(Z_angle<-3&&Z_angle>-40))
		status|=0b00001100;
		///////////////////////////
		//if((chk(PINF,0))==0)
		//status=0b10000001;  //left turn
		//
		//if((chk(PINF,1))==0)
		//status=0b10000010;  //right turn
		/////////////////////////
		switch(status)
		{
		//case 0b10000001:
		//drive_fb(0,rs);
		//break;
		//case 0b10000010:
		//drive_fb(ls,0);
		//break;
		case 0b00000000: drive_fb(ls,rs);
		off1();
		off4();
		off3();
		off2();
		break;
		case 0b00000001: drive_fb((ls-(dif*3)),rs);
		glow2();
		off1();
		off3();
		off4();
		break;
		case 0b00000101: drive_fb((ls-(dif*8)),rs);
		glow1();
		off4();
		off2();
		off3();
		break;
		case 0b00001101: drive_fb((ls-(dif*12)),rs);
		glow1();
		off4();
		off2();
		off3();
		break;
		
		case 0b00000010: drive_fb(ls,(rs-(dif*3)));
		glow3();
		off1();
		off4();
		off2();
		break;
		case 0b00000110: drive_fb(ls,(rs-(dif*8)));
		glow4();
		off2();
		off1();
		off3();
		break;
		case 0b00001110: drive_fb(ls,(rs-(dif*12)));
		glow4();
		off1();
		off2();
		off3();
		break;
		default: drive_fb(ls,rs);
		break;
		}			
			
	}	
}


void sidhawithstop(int dist,int ls,int rs,int dif)
{ 
	//proxy F0-left,F1-right
	
	char status;

			status=0;
//			_delay_ms(100);
         
		//LCDvar(0,0,maxon1,4);
		//LCDvar(0,1,Z_angle,5);
		if(Z_angle<-1)
		status|=0b00000001;  //left turn
		else if(Z_angle>1)
		status|=0b00000010;  //right turn
		///////////////////////
		if((Z_angle>1&&Z_angle<3)||(Z_angle<-1&&Z_angle>-3))
		status|=0b00000100;
		if((Z_angle>3&&Z_angle<40)||(Z_angle<-3&&Z_angle>-40))
		status|=0b00001100;
		///////////////////////////
		//if((chk(PINF,0))==0)
		//status=0b10000001;  //left turn
		//
		//if((chk(PINF,1))==0)
		//status=0b10000010;  //right turn
		/////////////////////////
		switch(status)
		{
		//case 0b10000001:
		//drive_fb(0,rs);
		//break;
		//case 0b10000010:
		//drive_fb(ls,0);
		//break;
		case 0b00000000: drive_fb(ls,rs);
		off1();
		off4();
		off3();
		off2();
		break;
		case 0b00000001: drive_fb((ls-(dif*3)),rs);
		glow2();
		off1();
		off3();
		off4();
		break;
		case 0b00000101: drive_fb((ls-(dif*8)),rs);
		glow1();
		off4();
		off2();
		off3();
		break;
		case 0b00001101: drive_fb((ls-(dif*12)),rs);
		glow1();
		off4();
		off2();
		off3();
		break;
		
		case 0b00000010: drive_fb(ls,(rs-(dif*3)));
		glow3();
		off1();
		off4();
		off2();
		break;
		case 0b00000110: drive_fb(ls,(rs-(dif*8)));
		glow4();
		off2();
		off1();
		off3();
		break;
		case 0b00001110: drive_fb(ls,(rs-(dif*12)));
		glow4();
		off1();
		off2();
		off3();
		break;
		default: drive_fb(ls,rs);
		break;
		}			
			
		
}

void ulta(int dist,int ls, int rs,int dif)
{
	maxon1=0; 
	char status;
	//dist=maxtemp+dist;
		while(maxon1<dist)
		{   
			status=0;
//			_delay_ms(100);
         
		LCDvar(0,0,maxon1,4);
		LCDvar(0,1,Z_angle,5);
		if(Z_angle<-2)
		status|=0b00000001;  //left turn
		else if(Z_angle>2)
		status|=0b00000010;  //right turn
		///////////////////////
		if((Z_angle>4&&Z_angle<6)||(Z_angle<-4&&Z_angle>-6))
		status|=0b00000100;
		if((Z_angle>6&&Z_angle<100)||(Z_angle<-6&&Z_angle>-100))
		status|=0b00001100;
		
		switch(status)
		{
		case 0b00000000: drive_fb(-(ls),-(rs));
		off1();
		off4();
		off3();
		off2();
		break;
		case 0b00000001: drive_fb(-(ls-(dif*3)),-(rs));
		glow2();
		off1();
		off3();
		off4();
		break;
		case 0b00000101: drive_fb(-(ls-(dif*8)),-(rs));
		glow1();
		off4();
		off2();
		off3();
		break;
		case 0b00001101: drive_fb(-(ls-(dif*12)),-(rs));
		glow1();
		off4();
		off2();
		off3();
		break;
		
		case 0b00000010: drive_fb(-(ls),-(rs-(dif*3)));
		glow3();
		off1();
		off4();
		off2();
		break;
		case 0b00000110: drive_fb(-(ls),-(rs-(dif*8)));
		glow4();
		off2();
		off1();
		off3();
		break;
		case 0b00001110: drive_fb(-(ls),-(rs-(dif*12)));
		glow4();
		off1();
		off2();
		off3();
		break;
		default: drive_fb(-(ls),-(rs));
		break;
		}			
			
	}	

	
}

void left(int dist,int ls,int rs,int dif)
{ 
	maxon1=0; 
	char status;
	//dist=maxtemp+dist;
		while(maxon1<dist)
		{   
			status=0;
//			_delay_ms(100);
         
		LCDvar(0,0,maxon1,4);
		LCDvar(0,1,Z_angle,5);
		if(Z_angle<-2)
		status|=0b00000001;  //left turn
		else if(Z_angle>2)
		status|=0b00000010;  //right turn
		///////////////////////
		if((Z_angle>4&&Z_angle<6)||(Z_angle<-4&&Z_angle>-6))
		status|=0b00000100;
		if((Z_angle>6&&Z_angle<100)||(Z_angle<-6&&Z_angle>-100))
		status|=0b00001100;
		
		switch(status)
		{
		case 0b00000000: drive_lr(ls,rs);
		off1();
		off4();
		off3();
		off2();
		break;
		case 0b00000001: drive_lr((ls-(dif*3)),rs);
		glow2();
		off1();
		off3();
		off4();
		break;
		case 0b00000101: drive_lr((ls-(dif*8)),rs);
		glow1();
		off4();
		off2();
		off3();
		break;
		case 0b00001101: drive_lr((ls-(dif*12)),rs);
		glow1();
		off4();
		off2();
		off3();
		break;
		
		case 0b00000010: drive_lr(ls,(rs-(dif*3)));
		glow3();
		off1();
		off4();
		off2();
		break;
		case 0b00000110: drive_lr(ls,(rs-(dif*8)));
		glow4();
		off2();
		off1();
		off3();
		break;
		case 0b00001110: drive_lr(ls,(rs-(dif*12)));
		glow4();
		off1();
		off2();
		off3();
		break;
		default: drive_lr(ls,rs);
		break;
		}			
			
	}	

		maxtemp=maxon1;
}

void right(int dist,int ls,int rs,int dif)
{
	maxon1=0; 
	char status;
	//dist=maxtemp+dist;
		while(maxon1<dist)
		{   
			status=0;
//			_delay_ms(100);
         
		LCDvar(0,0,maxon1,4);
		LCDvar(0,1,Z_angle,5);
		if(Z_angle>2)
		status|=0b00000001;  //left turn
		else if(Z_angle<-2)
		status|=0b00000010;  //right turn
		///////////////////////
		if((Z_angle>4&&Z_angle<6)||(Z_angle<-4&&Z_angle>-6))
		status|=0b00000100;
		if((Z_angle>6&&Z_angle<100)||(Z_angle<-6&&Z_angle>-100))
		status|=0b00001100;
		
		switch(status)
		{
		case 0b00000000: drive_lr(-(ls),-(rs));
		off1();
		off4();
		off3();
		off2();
		break;
		case 0b00000001: drive_lr(-(ls-(dif*3)),-(rs));
		glow2();
		off1();
		off3();
		off4();
		break;
		case 0b00000101: drive_lr(-(ls-(dif*8)),-(rs));
		glow1();
		off4();
		off2();
		off3();
		break;
		case 0b00001101: drive_lr(-(ls-(dif*12)),-(rs));
		glow1();
		off4();
		off2();
		off3();
		break;
		
		case 0b00000010: drive_lr(-(ls),-(rs-(dif*3)));
		glow3();
		off1();
		off4();
		off2();
		break;
		case 0b00000110: drive_lr(-(ls),-(rs-(dif*8)));
		glow4();
		off2();
		off1();
		off3();
		break;
		case 0b00001110: drive_lr(-(ls),-(rs-(dif*12)));
		glow4();
		off1();
		off2();
		off3();
		break;
		default: drive_lr(-(ls),-(rs));
		break;
		}			
			
	}	

}

ISR(INT4_vect)
{
	task=1;
	LCDvar(0,1,255,3);
	LCDvar(10,1,0,3);
}

ISR(INT2_vect)
{
   task=1;
   
   LCDvar(0,1,0,3);
	LCDvar(10,1,255,3);
}

#endif /* LOCOMOTION_H_ */
