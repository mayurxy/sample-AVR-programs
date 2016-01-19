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


extern volatile float X_angle,Y_angle,Z_angle,apna_angle,X_angle_prev=0,Y_angle_prev=0,Z_angle_prev=0;
extern volatile signed short int X_Data,Y_Data,Z_Data,temp,set1;
extern volatile signed short int Z_angle_mag,Z_angle_mag_current;
extern volatile unsigned char tem; 
extern volatile long int X_zero,Y_zero,Z_zero;
extern float zacc,xacc,yacc,total,xangle,yangle;
extern unsigned char check1;
extern volatile long  int ch1time,ch1on,ch2time,ch2on,ch3time,ch3on,ch4time,ch4on,ch1tmp,ch2tmp,ch3tmp,ch1tmp,task;
volatile int mean_1,mean_2,ontime_1,ontime_2,ontime_3;
volatile int frontmotor,rightmotor,leftmotor,backmotor;
volatile int power=0,roll=0,pitch=0,yaw=0;



unsigned int ADC_val(unsigned char ch)
{
	unsigned int adc;
	ADMUX=(1<<REFS0)|ch;		//2.56 REFERENCE
	ADCSRA|=(1<<ADSC)|(1<<ADPS1)|(1<<ADPS0);	
	while( !(ADCSRA & (1<<ADIF) ) );
	//ADCSRA|=(1<<ADIF);
	adc=ADCL;
	return (ADCH<<8)|adc;
}

int main(void)
{
	
	#define F_CPU 16000000UL
	
	//Init_LED();  
	uart_1_ini();

	PORTG=255;
		
	TWI_init_master(); 
	kalmaninit();
	
	_delay_ms(200);     
	cli();                //Initialize Gyro
	InitHMC();
	PORTG=0;    //Enable Global Interrupt
	DDRA=0;
	DDRD=0b00001011;
	PORTA=255;
	DDRF=0;
	_delay_ms(5);	
	cleargyro(); 
	zero_error(); 	
	sei();
	
	ADCSRA=(1<<ADEN);//|(1<<ADFR);	
	
	/*while (!load)
	{		
	}*/
		
    //init_timer();
	
	int i;
	
	
	//
	//while(1)
	//{
			//PORTG=255;
			//_delay_ms(1000);
			PORTG=0;
			//_delay_ms(1000);
	//}
	while(1)
	{
		zacc=((ADC_val(2)*5/1023.0)-1.63)/0.38;
		xacc=((ADC_val(0)*5/1023.0)-1.63)/0.33;//59
		yacc=((ADC_val(1)*5/1023.0)-1.70)/0.36;//66
		total=sqrt(zacc*zacc+xacc*xacc+yacc*yacc);
		xangle=asin(((-1)*xacc/total))*180/3.14;
		yangle=asin(((-1)*yacc/total))*180/3.14;
			
				frontmotor=ontime_1/10;
				backmotor=ontime_1/10;
				rightmotor=ontime_1/10;
				leftmotor=ontime_1/10;
		
		uart_1_Transmit('@');
		
		uartWriteInt(X_angle,4);
		
		uart_1_Transmit('$');
		uartWriteInt(Y_angle,4);
	    uart_1_Transmit('A');
	    uartWriteInt(ontime_1,4);
		uart_1_Transmit(13);

		
		
	}
}