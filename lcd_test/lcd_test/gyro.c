#include <avr/io.h>
#ifndef F_CPU
	#define F_CPU 16000000UL
#endif

#define left 1
#define right 4  //4
#define back 2//2
#define front 3 //3

#include <util/delay.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include "gyro.h"


volatile int frontmotor=0,rightmotor=0,leftmotor=0,backmotor=0;
volatile int counterpwm=0;

#define RTC_R 0xD3
#define RTC_W 0xD2
#define RS PB0
#define EN PB2
#define dataport PORTD


unsigned char address=0x20, read=1, write=1;
unsigned char write_data=0x01, recv_data;
 
volatile signed short int X_Data=0,Y_Data=0,Z_Data=0;
volatile float X_angle=0,Y_angle=0,Z_angle=0,apna_angle=0;
volatile signed short int temp=0;
volatile signed short int Z_angle_mag=0,Z_angle_mag_current=0,set1=0;
volatile long int X_zero=0,Y_zero=0,Z_zero=0;
volatile unsigned char tem=0; 
volatile float zacc,xacc,yacc,total,xangle,yangle,zangle;
volatile counter=0,counterz=0,counteracc=0;
volatile unsigned char check1=0;
extern volatile int mean_1,mean_2,ontime_1,ontime_2,ontime_3;

volatile char first_time=1,mean_temp=0;
volatile float X_mean,Y_mean;
volatile float X_new_angle=0,Y_new_angle=0;

 
volatile long int ch1time=0,ch1on=0,ch2time=0,ch2on=0,ch3time=0,ch3on=0,ch4time=0,ch4on=0,ch1tmp=0,ch2tmp=0,ch3tmp=0,ch4tmp=0,task=0;
   
ISR(TIMER2_COMP_vect)
{



	//PORTG=255;
TWBR=3;	
    // TCNT2=0;
	//tem=getdata(0x26)
	
	
	X_Data=getdata(0x28);
		temp=getdata(0x29);
		X_Data|=((signed short int)temp<<8);
	//LCDvar(10,0,TCNT2,5);
	
	Y_Data=getdata(0x2A);
		temp=getdata(0x2B);
		Y_Data|=((signed short int)temp<<8);
	
	Z_Data=getdata(0x2C);
		temp=getdata(0x2D);
		Z_Data|=((signed short int)temp<<8);
	
		
if(Z_Data<Z_zero&&Z_Data>0)
Z_Data=0;

if(Z_Data>(-Z_zero)&&Z_Data<0)
Z_Data=0;

if(Y_Data<Y_zero&&Y_Data>0)
Y_Data=0;

if(Y_Data>(-Y_zero)&&Y_Data<0)
Y_Data=0;

if(X_Data<X_zero&&X_Data>0)
X_Data=0;

if(X_Data>(-X_zero)&&X_Data<0)
X_Data=0;
	

Z_angle=(float)Z_angle+((float)Z_Data*0.07*0.00768);

X_angle=(float)X_angle+((float)X_Data*0.07*0.00768);
Y_angle=(float)Y_angle+((float)Y_Data*0.07*0.00768);

	

temp=TCNT2;
TCNT2=temp;

counteracc++;
if (X_angle==360||X_angle==-360)
{
	X_angle=0;
}
if (Y_angle==360||Y_angle==-360)
{
	Y_angle=0;
}	
if (Z_angle==360||Z_angle==-360)
{
	Z_angle=0;
}		



}
 

void TWI_init_master(void) // Function to initialize master
{
	TWBR=3;	// Bit rate
	TWSR=(0<<TWPS1)|(0<<TWPS0);	// Setting prescalar bits
	PORTD|=(1<<0)|(1<<1);
	// SCL freq= F_CPU/(16+2(TWBR).4^TWPS)
	TCCR2=0b00001101;
 TIMSK|=1<<OCIE2;
	OCR2=120;
	TWI_start(); 
		TWI_write_address(0xD2); 
		TWI_write_data(0x20);	 
	TWI_write_data(0b11101111);
		TWI_stop(); 
		TWI_start(); 
		TWI_write_address(0xD2); 
		TWI_write_data(0x23);	 
	TWI_write_data(0b00100000);
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
	while(!(TWCR & (1<<TWINT))); // Wait till start condition is transmitted
	while((TWSR & 0xF8)!= 0x08); // Check for the acknowledgment
}
 
void TWI_repeated_start(void)
{
	// Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
	TWCR= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);	
	while(!(TWCR & (1<<TWINT))); // wait till restart condition is transmitted
	while((TWSR & 0xF8)!= 0x10); // Check for the acknoledgement
}
 
void TWI_write_address(unsigned char data)
{
	TWDR=data;	// Address and write instruction
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
	while((TWSR & 0xF8)!= 0x18);  // Check for the acknoledgement
}
 
void TWI_read_address(unsigned char data)
{
	TWDR=data;	// Address and read instruction
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte received
	while((TWSR & 0xF8)!= 0x40);  // Check for the acknoledgement
}
 
void TWI_write_data(unsigned char data)
{
	TWDR=data;	// put data in TWDR
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
	while((TWSR & 0xF8) != 0x28); // Check for the acknoledgement
}
 
unsigned char TWI_read_data(void)
{
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
	while((TWSR & 0xF8) != 0x58); // Check for the acknoledgement
	return TWDR;

	
}
  
void TWI_stop(void)
{
	// Clear TWI interrupt flag, Put stop condition on SDA, Enable TWI
	TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);	
	while((TWCR & (1<<TWSTO)));  // Wait till stop condition is transmitted
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
	for(i=0;i<200;i++)
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
		_delay_ms(5);
	if (X_Data>=0)
	{
	X_zero=X_zero+X_Data;
	}
    else if (X_Data<0)
	{
		X_Data= X_Data*(-1);
	X_zero=X_zero+X_Data;
	}
		
	if (Y_Data>=0)
	{
	Y_zero=Y_zero+Y_Data;
	}
    else if (Y_Data<0)
	{
		Y_Data= Y_Data*(-1);
	Y_zero=Y_zero+Y_Data;
	}
	
	if (Z_Data>=0)
	{
	Z_zero=Z_zero+Z_Data;
	}
    else if (Z_Data<0)
	{
		Z_Data= Z_Data*(-1);
	Z_zero=Z_zero+Z_Data;
	}
		
	
		
	}
	X_zero=X_zero/200;
	
	Y_zero=Y_zero/200;
	
	Z_zero=Z_zero/200;
	
}



