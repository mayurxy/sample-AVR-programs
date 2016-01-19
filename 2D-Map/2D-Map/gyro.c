#include <avr/io.h>
#ifndef F_CPU
	#define F_CPU 16000000UL
#endif


#include <util/delay.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include "gyro.h"
#include "mydefs.h"
#include "lcd.h"
#define RTC_R 0xD3
#define RTC_W 0xD2
#define RS PB0
#define EN PB2
#define dataport PORTD
#define lmtlp 60

unsigned char address=0x20, read=1, write=1;
unsigned char write_data=0x01, recv_data;
 
volatile signed short int X_Data=0,Y_Data=0,Z_Data=0;
volatile float X_angle=0,Y_angle=0,Z_angle=0;
volatile signed short int temp=0;
volatile long X_zero=0,Y_zero=0,Z_zero=-300;
uint16_t lpbrk=lmtlp , flgbrk=0;

ISR(TIMER2_COMP_vect)
{
glow2();
glow3();
     
		Z_Data=getdata(0x2C);
		temp=getdata(0x2D);
		Z_Data|=((signed short int)temp<<8);
	
	
		
if(Z_Data<200&&Z_Data>0)
Z_Data=0;

if(Z_Data>(-200)&&Z_Data<0)
Z_Data=0;
	
if(!flgbrk)
{
	Z_angle=(float)Z_angle+((float)Z_Data*0.0000161875);//*8.75 *0.002*0.000925);
	//flgbrk=0;	
}
flgbrk=0;
///0.925ms+
off2();
off3();
 }
/////////////////Functions/////////////////////////////////
void TWI_init_master(void) // Function to initialize master
{
	TWBR=3;	// Bit rate
	TWSR=(0<<TWPS1)|(0<<TWPS0);	// Setting prescalar bits
	PORTD|=(1<<0)|(1<<1);
	// SCL freq= F_CPU/(16+2(TWBR).4^TWPS)
	TCCR2=0b00001011;
	 TIMSK|=1<<OCIE2;
		OCR2=200;
		TWI_start(); 
		TWI_write_address(0xD2); 
		TWI_write_data(0x20);	 
		TWI_write_data(0b11101111);
		TWI_stop(); 
		TWI_start(); 
		TWI_write_address(0xD2); 
		TWI_write_data(0x23);	 
		TWI_write_data(0b00010000);
		TWI_stop(); 

}
 
 void disable_gyro()
 {
	// TCCR2=0;
	 TIMSK&=(~(1<<OCIE2));
	 //TWCR=0;
 }
void TWI_start(void)
{
	// Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
	TWCR= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);	
	while((!(TWCR & (1<<TWINT)))&&(lpbrk--));
	if(!lpbrk)
	flgbrk=1;
	lpbrk=lmtlp;
	
	while(((TWSR & 0xF8)!= 0x08)&&(lpbrk--));// Check for the acknowledgment
	if(!lpbrk)
	flgbrk=1;
	lpbrk=lmtlp; 
	
}
 
void TWI_repeated_start(void)
{
	// Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
	TWCR= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);	
	while((!(TWCR & (1<<TWINT)))&&(lpbrk--));
	if(!lpbrk)
	flgbrk=1;
	lpbrk=lmtlp; // wait till restart condition is transmitted
	while(((TWSR & 0xF8)!= 0x10)&&(lpbrk--));
	if(!lpbrk)
	flgbrk=1;
	lpbrk=lmtlp; // Check for the acknoledgement
}
 
void TWI_write_address(unsigned char data)
{
	TWDR=data;	// Address and write instruction
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while( (!(TWCR & (1<<TWINT)))&&(lpbrk--));
	if(!lpbrk)
	flgbrk=1;
	lpbrk=lmtlp; // Wait till complete TWDR byte transmitted
	while(((TWSR & 0xF8)!= 0x18)&&(lpbrk--));
	if(!lpbrk)
	flgbrk=1;
	lpbrk=lmtlp;  // Check for the acknoledgement
}
 
void TWI_read_address(unsigned char data)
{
	TWDR=data;	// Address and read instruction
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while( (!(TWCR & (1<<TWINT)))&&(lpbrk--));
	if(!lpbrk)
	flgbrk=1;
	lpbrk=lmtlp; // Wait till complete TWDR byte received
	while(((TWSR & 0xF8)!= 0x40)&&(lpbrk--));
	if(!lpbrk)
	flgbrk=1;
	lpbrk=lmtlp;  // Check for the acknoledgement
}
 
void TWI_write_data(unsigned char data)
{
	TWDR=data;	// put data in TWDR
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while( (!(TWCR & (1<<TWINT)))&&(lpbrk--));
	if(!lpbrk)
	flgbrk=1;
	lpbrk=lmtlp; // Wait till complete TWDR byte transmitted
	while(((TWSR & 0xF8) != 0x28)&&(lpbrk--));
	if(!lpbrk)
	flgbrk=1;
	lpbrk=lmtlp; // Check for the acknoledgement
}
 
unsigned char TWI_read_data(void)
{
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while( (!(TWCR & (1<<TWINT)))&&(lpbrk--));
	if(!lpbrk)
	flgbrk=1;
	lpbrk=lmtlp; // Wait till complete TWDR byte transmitted
	while(((TWSR & 0xF8) != 0x58)&&(lpbrk--));
	if(!lpbrk)
	flgbrk=1;
	lpbrk=lmtlp; // Check for the acknoledgement
	return TWDR;

	
}
  
void TWI_stop(void)
{
	// Clear TWI interrupt flag, Put stop condition on SDA, Enable TWI
	TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);	
	while(((TWCR & (1<<TWSTO)))&&(lpbrk--));
	if(!lpbrk)
	flgbrk=1;
	lpbrk=lmtlp;  // Wait till stop condition is transmitted
}

signed short int getdata(unsigned char add)
{
        signed short int DATA; 
        TWI_start(); 
		TWI_write_address(0xD2); 
		TWI_write_data(add);	
		
		TWI_repeated_start();	
		TWI_read_address(0xD3);	
		DATA=TWI_read_data();		
		TWI_stop();
		return DATA;

}
void zero_error(void)
{
	
	int i=0;
	for(i=0;i<100;i++)
	{
		
		X_Data=getdata(0x28);		
		temp=getdata(0x29);
    	X_Data|=((signed short int)temp<<8);
		
		Y_Data=getdata(0x2A);
		temp=getdata(0x2B);
		Y_Data|=((signed short int)temp<<8);
		
		Z_Data=getdata(0x2C);
		temp=getdata(0x2D);
		Z_Data|=((signed short int)temp<<8);
	
	X_zero=X_zero+X_Data;
	Y_zero=Y_zero+Y_Data;
	Z_zero=Z_zero+Z_Data;
	
	
		
	}
	X_zero=X_zero/100;
	
	Y_zero=Y_zero/100;
	
	Z_zero=Z_zero/100;
	
}
