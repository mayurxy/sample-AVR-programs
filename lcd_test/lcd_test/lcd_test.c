/*
 * lcd_test.c
 *
 * Created: 25-06-2013 22:18:05
 *  Author: Mayur
 */ 

#include <avr/io.h>
//#ifndef F_CPU
	#define F_CPU 16000000UL
//#endif
#include <avr/interrupt.h>
#include "lcd.h"
#include "gyro.h"
#include "uart.h"
#include "mydefs.h"
#include "gsm.h"
#include "GPS.h"
//#include <inttypes.h>

#include <util/delay.h>

extern volatile float X_angle,Y_angle,Z_angle;
extern volatile signed short int X_Data,Y_Data,Z_Data;
extern volatile unsigned char lati[11],longi[12],time[9],date[6],speed[5],valid;

void sendlocation(unsigned char *num);

int main(void)
{
	//int flag;
	
	TWI_init_master();
	_delay_ms(100);
	//sei();
	//_delay_ms(1000);
	InitLCD(0);
	_delay_ms(50);
	LCDClear();
	_delay_ms(10);
    uart_0_ini();
	uart_1_ini();
        Init_LED();
		sei();
		_delay_ms(50);
		
		LCD(0,0,"VIT");
		_delay_ms(500);
		LCDClear();
		_delay_ms(10);
		LCD(0,0,"SURACSHA");
		_delay_ms(100);
		LCDClear();
		_delay_ms(100);
	
	
		while (1)
		{
LCDvar(0,0,Y_Data,5);
 		if (Y_Data > 2000 || Y_Data < -2000 ||X_Data > 2000 || X_Data < -2000||Z_Data > 2000 || Z_Data < -2000)
 		{
				_delay_ms(50);
 					LCDClear();
 					_delay_ms(70);
 				LCD(0,1,"accident Happned");
 				//flag=1;
 				glow3();
 				glow4();

 				 LCDGotoXY(0,0);
			LCDWriteString("Waiting for GPS");
 			while(valid!='A');
 			 LCDClear();
				 _delay_ms(100);
			 LCDGotoXY(0,0);
 			LCDWriteString("Fix Available");
 				_delay_ms(2000);
				 LCDClear();
				 _delay_ms(100);
 				 sendlocation("9503139115");
 				//break;
 		}		
 		else
 		{_delay_ms(70);
 		 LCDGotoXY(0,1);
	LCDWriteString("Normal");
 		glow2();
 		glow3();
 		_delay_ms(50);
 		off2();
 		off3();
 
	}

			
		 }}	

void sendlocation(unsigned char *num)
{
	int k;
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
	stringuart1("accident happened at");
	
	uart_1_Transmit(13);
	stringuart1("longi=");
	for(k=0;k<12;k++)	
			uart_1_Transmit(longi[k]);
		
	uart_1_Transmit(13);
	stringuart1("latti=");
		for(k=0;k<11;k++)	
			uart_1_Transmit(lati[k]);
	
	uart_1_Transmit(13);
	
	stringuart1("time=");
		for(k=0;k<11;k++)	
			uart_1_Transmit(time[k]);
	
	uart_1_Transmit(26);
	
	
	}	
}

		