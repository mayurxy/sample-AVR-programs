/*
 * Biomedical.c
 *
 * Created: 1/1/2013 2:27:55 PM
 *  Author: Pranav
 */ 
#define left 1
#define right 4  //4
#define back 2//2
#define front 3 //3
 
 
#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>
#include "uart.h"
#include "lcd.h"
#include "GPS.h"
#include "gsm.h"
#include "gyro.h"
#include "pwm.h"
#include "reciever.h"


extern volatile float X_angle,Y_angle,Z_angle,apna_angle,Y_angle_prev=0,X_angle_prev=0,X_error=0,X_integ=0;
extern volatile signed short int X_Data,Y_Data,Z_Data,temp,set1;
extern volatile signed short int Z_angle_mag,Z_angle_mag_current;
extern volatile unsigned char tem; 
extern volatile long int X_zero,Y_zero,Z_zero;
extern float zacc,xacc,yacc,total,xangle,yangle;
extern unsigned char check1;
extern volatile long  int ch1time,ch1on,ch2time,ch2on,ch3time,ch3on,ch4time,ch4on,ch1tmp,ch2tmp,ch3tmp,ch1tmp,task;
volatile int mean_1,mean_2,ontime_1,ontime_2,ontime_3;
volatile int frontmotor,rightmotor,leftmotor,backmotor;
volatile int gain;
volatile int power=0,roll=0,pitch=0,yaw=0;
int Y_error=0,Y_integ=0;
extern volatile float X_new_angle,Y_new_angle;
extern volatile float Xangle,Yangle;
float windupguard=0;


int main(void)
{
	PORTG=255;
	_delay_ms(2000);
	
	#define F_CPU 16000000UL
	unsigned char temp;
	//Init_LED();  
	uart_1_ini();
	
	while (temp=='P')
	{
	temp=USART1_Recieve();	
	}
	temp=0;
	while (temp<5)
	{
		uart_1_Transmit('o');
	temp++;
	 }
	
	
		
		UCSR1B=((1<<RXEN1)|(1<<TXEN1)|(1<<RXCIE1));
	PORTG=0;	
	TWI_init_master(); 
	//kalmaninit();
	PORTG=255;
	uart_1_Transmit('B');
	_delay_ms(200);     
	cli();                //Initialize Gyro
	InitHMC();
	PORTG=0;    //Enable Global Interrupt
	DDRA=0;
	DDRD=0b00001011;
	PORTA=255;
	DDRF=0;
	//ADCSRA=(1<<ADEN);//|(1<<ADFR);	
	_delay_ms(5);	
	cleargyro(); 
	zero_error(); 	
	sei();
	
	PORTG=0;
	//uart_1_Transmit('C');

	//uart_1_Transmit('L');	
    //init_timer();
	//_delay_ms(500);
	
	/*_delay_ms(2000);
	
	setspeed(front,100);
	setspeed(left,0);
	setspeed(right,0);
	setspeed(back,0);
	
	_delay_ms(500);
	
	setspeed(front,0);
	setspeed(left,100);
	setspeed(right,0);
	setspeed(back,0);
	
	_delay_ms(1000);
	
	setspeed(front,0);
	setspeed(left,0);
	setspeed(right,100);
	setspeed(back,0);
	
	_delay_ms(1000);
	
	setspeed(front,0);
	setspeed(left,0);
	setspeed(right,0);
	setspeed(back,100);
	
	_delay_ms(2000);
	
	setspeed(front,0);
	setspeed(left,0);
	setspeed(right,0);
	setspeed(back,0);
	*/
	//OCR0=18;
	int i,countera=0;
	
	
	//
	//while(1)
	//{
			//PORTG=255;
			//_delay_ms(1000);
		//	PORTG=0;
			//_delay_ms(1000);
	//}
	while(1)
	{
		
	
		
		/*	  PORTG=!(PORTG);
				frontmotor=ontime_1;
				backmotor=ontime_1;
				rightmotor=ontime_1;
				leftmotor=ontime_1;
		*/
				
		 //if (X_angle>4 || X_angle < (-4))
		//{
		//
		//leftmotor=leftmotor-Y_angle*0.3;
		//rightmotor=rightmotor+Y_angle*0.3;
		//} 
		
		
		
				if(X_angle>X_angle_prev)
				X_error=X_angle-X_angle_prev;
				else
				X_error=X_angle_prev-X_angle;
				
				X_integ =X_integ+Xangle;
				if (X_integ>=5000)
					X_integ=5000;
				if (X_integ<=-5000)
				X_integ=-5000;
				countera++;
				
				
		if (X_angle>2)
		{
		float kp=0.8;
		float kd=0.6;
		float ki=0.005;
		leftmotor=ontime_1+kp*X_angle+kd*X_error+ki*X_integ;
		if(leftmotor<0)
			leftmotor=0;
		rightmotor=ontime_1-kp*X_angle-kd*X_error-ki*X_integ;	
		if(rightmotor<0)
			rightmotor=0;
		X_angle_prev=X_angle;
		}
		else if (X_angle<-2)
		{
		float kp=0.8;
		float kd=0.6;
		float ki=0.005;  // 0.0012
		leftmotor=ontime_1+kp*X_angle-kd*X_error+ki*X_integ;
		if(leftmotor<0)
			leftmotor=0;
		rightmotor=ontime_1-kp*X_angle+kd*X_error-ki*X_integ;	
		if(rightmotor<0)
			rightmotor=0;
		X_angle_prev=X_angle;
		}
		else
		{
			rightmotor=ontime_1;
			leftmotor=ontime_1;
		}			
				
			leftmotor=ontime_1;
			rightmotor=ontime_1;
		//setspeed(front,frontmotor);
		setspeed(left,leftmotor);
		setspeed(right,rightmotor);
		////setspeed(back,backmotor);	
		//
		
		//uart_1_Transmit('Y');
		//uartWriteInt(Y_angle,4);
		//uart_1_Transmit('y');
		//uartWriteInt(Yangle,4);
		//uart_1_Transmit('X');
		//uartWriteInt(Xangle,4);
		uart_1_Transmit('X');
		uartWriteInt(Xangle,4);
		uart_1_Transmit('x');
		uartWriteInt(yangle,4);
		
		//uart_1_Transmit('Y');
		//uartWriteInt(Yangle,4);
		uart_1_Transmit('Y');
		uartWriteInt(Yangle,4);
		uart_1_Transmit('y');
		uartWriteInt(xangle,4);
		//uart_1_Transmit('Z');
		//uartWriteInt(zacc*100,4);
		//uart_1_Transmit('I');
        //uartWriteInt(X_integ,6);
		//uart_1_Transmit('C');
        //uartWriteInt(countera,6);
		
		uart_1_Transmit(13);
		//uart_1_Transmit('Y');
		//uartWriteInt(yacc*100,4);
		//uart_1_Transmit('X');
		//uartWriteInt(xacc*100,4);
		
	////	*/
        /*uart_1_Transmit('F');
	    uartWriteInt(frontmotor,4);
		uart_1_Transmit('B');
	    uartWriteInt(backmotor,4);
		uart_1_Transmit('R');
		uartWriteInt(load,1);
////		*/
		/*
		uart_1_Transmit('L');
		uartWriteInt(load,1);
		uart_1_Transmit('L');
		uart_1_Transmit('&');
		uartWriteInt(mean_1,3);
		uart_1_Transmit('&');
		uartWriteInt(mean_2,3);	
		uart_1_Transmit('&');
		uartWriteInt(ontime_1,4);
		uart_1_Transmit('&');
		uartWriteInt(ontime_2,4);
		uart_1_Transmit('&');
		uartWriteInt(ontime_3,4);
		*/
		
	}
}