#include <avr/io.h>
//#ifndef F_CPU
	#define F_CPU 16000000UL
//#endif
#include <avr/interrupt.h>
#include "lcd.h"
//#include "gyro.h"
#include "gsm.h"
#include "GPS.h"
#include "uart.h"
#include <util/delay.h>
extern volatile unsigned char lati[11],longi[12],time[9],date[6],speed[5],valid;


int main(void)
{
	           
   
 _delay_ms(1000);
	InitLCD(0);
	_delay_ms(50);
	LCDClear();
	_delay_ms(10);
	Init_LED();
	_delay_ms(50);
	_delay_ms(50);
	uart_1_ini();
	uart_0_ini();

	_delay_ms(1000);

	sei();
	
	LCDClear();
	_delay_ms(200);
	LCDGotoXY(0,0);
	LCDWriteString("Waiting");
	while(valid!='A');
	LCDGotoXY(0,0);
	LCDWriteString("Fix Available");
	
	
	
	sendlocation("9503139115");

		
   


}	

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
	stringuart1("Valid=YES");
	
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
