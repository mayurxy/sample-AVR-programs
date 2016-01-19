#include <avr/io.h>
#include <avr/interrupt.h>
#include "motors.h"
#include "lcd.h"
#include "gyro.h"
#include "globalvariables.h"

extern volatile float X_angle,Y_angle,Z_angle;

#ifndef F_CPU
	#define F_CPU 16000000UL
#endif

#include <util/delay.h>
#include"mydefs.h"

volatile signed char speed;
unsigned char l_flag,r_flag,f_flag,b_flag,l_done,r_done,f_done,b_done;
volatile unsigned char l_count,r_count,f_count,b_count,linetracestart;
extern volatile uint8_t programstatus;
void init_t0()
{
	TCCR0=(1<<COM01)|(1<<WGM00)|(1<<WGM01)|(1<<CS01); // prescalar 8
	OCR0=0;
	TCNT0=0;
}

void init_t1()
{
	TCCR1A=(1<<COM1A1)|(1<<COM1B1)|(1<<COM1C1)|(1<<WGM10);  // prescalar 8
	TCCR1B=(1<<WGM12)|(1<<CS11);
	OCR1A=0;
	OCR1B=0;
	OCR1C=0;
	TCNT1=0;
}

void calculate(signed int val)
{
	
	
}
void decide(signed int a , signed int b , signed int c, signed int d)
{
	if(a>=0)
	{
		drive_mot(r_motor , a );
	}
	else if(a<0)
	{
		
		drive_mot(r_motor , -a);
	}
	
}


void drive_mot(unsigned char mot_no,signed int speed) 
{

if(speed>0)
 {
	switch(mot_no)
	{

	case 1:
			OCR1A=speed;
   			set(m1_p_2,m1_2);
			clr(m1_p_3,m1_3);		
			break;
	
	case 2: 
			OCR1B=(speed);
			set(m2_p_2,m2_2);
   			clr(m2_p_3,m2_3);	
			break;







	case 3:
			OCR1C=(speed);
   			clr(m3_p_2,m3_2);
			set(m3_p_3,m3_3);		
			break;
	
				
	case 4: 
			OCR0=speed;
			clr(m4_p_2,m4_2);
   			set(m4_p_3,m4_3);	
			break;
	
	
	}

 }

else if(speed==0)
 {
	switch(mot_no)
	{

	case 1:
			OCR1A=speed;
   			set(m1_p_2,m1_2);
			set(m1_p_3,m1_3);		
			break;
	
	case 2: 
			OCR1B=speed;
			set(m2_p_2,m2_2);
   			set(m2_p_3,m2_3);	
			break;

	case 3:
			OCR1C=speed;
   			set(m3_p_2,m3_2);
			set(m3_p_3,m3_3);		
			break;
	
	case 4: 
			OCR0=speed;
			set(m4_p_2,m4_2);
   			set(m4_p_3,m4_3);	
			break;
	
	
	}

 }

else
 {
	switch(mot_no)
	{

	case 1:
			OCR1A=(-speed);
   			clr(m1_p_2,m1_2);
			set(m1_p_3,m1_3);		
			break;
	
	case 2: 
			OCR1B=(-speed);
			clr(m2_p_2,m2_2);
   			set(m2_p_3,m2_3);	
			break;
			
	case 3:
			OCR1C=(-speed);
   			set(m3_p_2,m3_2);
			clr(m3_p_3,m3_3);		
			break;

	case 4: 
			OCR0=(-speed);
			set(m4_p_2,m4_2);
   			clr(m4_p_3,m4_3);	
			break;
	
	
	}

 } 

}//end drive_mot


void drive_fb(signed int l_speed, signed int r_speed)	//(left,right)
{

	drive_mot(l_motor,l_speed);
	drive_mot(r_motor,r_speed);

}

void drive_lr(signed int l_speed, signed int r_speed)	//(back,front)
{

	drive_mot(b_motor,l_speed);
	drive_mot(f_motor,r_speed);

}
/*
void go_till_line_f(signed char l_speed, signed char r_speed)
{

drive_fb(l_speed,r_speed);

l_count=0;
r_count=0;

l_flag=1;
r_flag=1;
l_done=1;
r_done=1;

while((l_flag || r_flag))                       
{
	if(l_count>0 && l_done==1)
	{
		drive_mot(l_motor,0);
		l_done=0;
		l_flag=0;
	}
	if(r_count>0 && r_done==1)
	{
		drive_mot(r_motor,0);
		r_done=0;
		r_flag=0;
	}
	LCDvar(0,0,OCR1C,3);
	LCDvar(6,0,OCR0,3);
}

drive_fb(0,0);

}


void go_till_line_b(signed char l_speed, signed char r_speed)
{
drive_fb(-l_speed,-r_speed);

l_count=0;
r_count=0;

l_flag=1;
r_flag=1;
l_done=1;
r_done=1;

while((l_flag || r_flag))                       
{
	if(l_count>0 && l_done==1)
	{
		drive_mot(l_motor,0);
		l_done=0;
		l_flag=0;
	}
	if(r_count>0 && r_done==1)
	{
		drive_mot(r_motor,0);
		r_done=0;
		r_flag=0;
	}
	

}

drive_fb(0,0);

}

void go_till_line_l(signed char b_speed, signed char f_speed)      //for +ve speed bot goes left
{

drive_lr(b_speed,f_speed);

b_count=0;
f_count=0;

b_flag=1;
f_flag=1;
b_done=1;
f_done=1;

while((b_flag || f_flag))                       
{
	if(b_count>0 && b_done==1)
	{
		drive_mot(b_motor,0);
		b_done=0;
		b_flag=0;
	}
	if(f_count>0 && f_done==1)
	{
		drive_mot(f_motor,0);
		f_done=0;
		f_flag=0;
	}
	

}

drive_lr(0,0);


}

void go_till_line_r(signed char b_speed, signed char f_speed)
{

drive_lr(-b_speed,-f_speed);

b_count=0;
f_count=0;

b_flag=1;
f_flag=1;
b_done=1;
f_done=1;

while((b_flag || f_flag))                       
{
	if(b_count>0 && b_done==1)
	{
		drive_mot(b_motor,0);
		b_done=0;
		b_flag=0;
	}
	if(f_count>0 && f_done==1)
	{
		drive_mot(f_motor,0);
		f_done=0;
		f_flag=0;
	}
	

}

drive_lr(0,0);

}





void go_till_line_l2(signed char b_speed, signed char f_speed)      //for +ve speed bot goes left
{
l_count=0;
drive_lr(b_speed,f_speed);

while(l_count==0);
drive_lr(0,0);

}
*/
/*************Send com*************/
void send_com(uint8_t data)
{
	
	set(DDRD,4);
	set(DDRD,5);
	set(DDRD,6);
	switch(data)
	{
		case 0:
		off1();
		off2();
		off3();
		clr(PORTD,4);
		clr(PORTD,5);
		clr(PORTD,6);
		break;
	case 1:
		glow1();
		off2();
		off3();
		set(PORTD,4);
		clr(PORTD,5);
		clr(PORTD,6);
		break;
	case 2:
		off1();
		glow2();
		off3();
		clr(PORTD,4);
		set(PORTD,5);
		clr(PORTD,6);
		break;
	case 3:
		glow1();
		glow2();
		off3();
		set(PORTD,4);
		set(PORTD,5);
		clr(PORTD,6);
		break;
	case 4:
		off1();
		off2();
		glow3();
		clr(PORTD,4);
		clr(PORTD,5);
		set(PORTD,6);
		break;
	case 5:
		glow1();
		off2();
		glow3();
		set(PORTD,4);
		clr(PORTD,5);
		set(PORTD,6);
		break;
	case 6:
		off1();
		glow2();
		glow3();
		clr(PORTD,4);
		set(PORTD,5);
		set(PORTD,6);
		break;
	case 7:
		glow1();
		glow2();
		glow3();
		set(PORTD,4);
		set(PORTD,5);
		set(PORTD,6);
		break;
	}
	glow4();
	set(PORTG,4);
	_delay_ms(100);
	clr(PORTG,4);
	off4();
}

/************ISR'S**********/


ISR(L2_grid)
{
	 
b_count++;	
}

//ISR(F_grid)
//{
//f_count++;
//}
//
//ISR(B_grid)
//{
//b_count++;
//}

/*ISR(INT7_vect)
{
	//LCDClear();
	
	char a=(PIND&0b01110000)>>4;
	LCDvar(0,1,a,2);
	switch(a)
	{
		
		case 1:
		programstatus=1;
		break;

		case 2:
		programstatus=2;
		break;
		
		case 3:
		programstatus=3;
		break;
		
		case 4:
		programstatus=4;
		break;
		
		case 5:
		programstatus=5;
		break;
		
		case 6:
		programstatus=6;
		break;

		case 7:
		programstatus=7;
		break;
	}
	}

*/