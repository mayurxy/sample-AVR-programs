/*
 * hmc.h
 *
 * Created: 31/07/2013 12:58:56
 *  Author: pranav
 */ 
#include <avr/io.h>
#include "uart.h"
//#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

#define TW_START 0x08
#define TW_REP_START 0x10
#define TW_MT_SLA_ACK 0x18

#ifndef HMC_H_
#define HMC_H_


////Call InitHMC to initailize
////Call InitRead to initialize reading
////Call HMC for values
volatile uint8_t f=0;
long x1=0, x2=0, data=0, dec=0, pnt=0, count=0;
volatile int no=0;
void error();

void pause()
{
_delay_ms(50);
}

void wait()
{
while(!(TWCR&(1<<TWINT)));//wait
}



void InitHMC()
{
TWBR=0b00001000;
TWSR|=(0<<TWPS0);
//LCD(7,1,"HMCINT");
pause();
}

void StrtHMC()
{
TWCR|=((1<<TWINT)|(1<<TWSTA)|(1<<TWEN));//initialize hmc 
wait();
if (((TWSR & 0xF8) != TW_START))
error();
//LCD(7,1,"STARTH");
//pause();
}


void RepStrtHMC()
{
TWCR|=((1<<TWINT)|(1<<TWSTA)|(1<<TWEN));//initialize hmc 
wait();
if (((TWSR & 0xF8) != TW_REP_START))
error();
//LCD(7,1,"RSTRTH");
//pause();
}

void StpHMC()
{
TWCR = ((1<<TWINT)|(1<<TWEN)|(1<<TWSTO));//stop hmc
//LCD(7,1,"STOPHM");
_delay_ms(30);
//wait();
//if ((TWSR & 0xF8) != 0x08)
}

void error()
{
switch(TWSR)
{
case 0x38:	StpHMC();
			StrtHMC();
			break;
case 0x58:
case 0x48:	RepStrtHMC();
			StpHMC();
			StpHMC();
			StrtHMC();
			break;
case 0x00: break;
default:break;
		//LCD(1,1,"Unknown");
		//_delay_ms(1500);
		//LCDvar(1,1,TWSR,5);
		//_delay_ms(2000);
		//LCDClear();
}
}
void WrtHMCAdd(uint8_t data)
{
TWDR=data;//load address
TWCR = ((1<<TWINT) |(1<<TWEN));//|(1<<TWEA));//send address
wait();
if (((TWSR & 0xF8) != TW_MT_SLA_ACK)&(((TWSR & 0xF8) != 0x18)))
error();
//LCD(7,1,"WRTADD");
//pause();
}

void WrtHMCAddasRec(uint8_t data)
{
//_delay_ms(1000);
TWDR=data;//load address
TWCR = ((1<<TWINT) |(1<<TWEN)|(1<<TWEA));//send address
wait();
if (((TWSR & 0xF8) != 0x40))
error();
//LCD(7,1,"WRTRADR");
//pause();
}

void WrtHMCData(uint8_t data)
{
TWCR|=(1<<TWINT);
TWDR=data;//load address
TWCR = ((1<<TWINT) |(1<<TWEN));//|(1<<TWEA));//send address
wait();
if (((TWSR & 0xF8) != 0x28)&(((TWSR & 0xF8) != 0x30)))
error();
//LCD(7,1,"HMCDTA");
//pause();
}



void InitRead()
{
	
TWBR=0x12;
TWDR=0xFF;
f=0;
StrtHMC();
WrtHMCAdd(0x42);
WrtHMCData(0x47);
WrtHMCData(0x74);
WrtHMCData(0x72);
_delay_ms(1);
WrtHMCData(0x4C);
_delay_ms(1);
StpHMC();
}

int HMC()
{
{
	
TWBR=0x12;
StrtHMC();
WrtHMCAddasRec(0x43);
x1=ReadHMC(0x1);
x2=ReadHMC(0x0);
data=((x1<<8)+x2);
dec=data/10;
//LCDvar(5,0,dec,4);
StpHMC();
no++;
return dec;
}
}


int ReadHMC(int ack)
{
	
	TWBR=0x12;
	cli();
uint8_t x;
if(ack==0)
TWCR = ((1<<TWINT) |(1<<TWEN));
if(ack==1)
TWCR = ((1<<TWINT)|(1<<TWEN)|(1<<TWEA));//send address
wait();
//_delay_ms(10);
x=TWDR;
if(ack==1)
{
if (((TWSR & 0xF8) != 0x50))
error();
}

return (x);
}



#endif /* HMC_H_ */