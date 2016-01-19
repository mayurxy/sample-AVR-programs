/*
 * linetrace.c
 *
 * Created: 9/18/2012 5:29:01 PM
 *  Author: Bakshi
 */ 
#include <avr/io.h>
#ifndef F_CPU
	#define F_CPU 16000000UL
#endif

#include <util/delay.h>
#include "linetrace.h"
#include "mydefs.h"
#include "motors.h"
#include "lcd.h"

#define lft 2
#define rt 1
#define strt 0

volatile unsigned char flag=strt;
unsigned int sensor;


void lsensor_test()
{

unsigned char i;

sensor = PINF;

for(i=0;i<7;i++)
	{
	if(chk(sensor,i))
		{
		LCD(i,1,"1");
		}
	else
		{
		LCD(i,1,"0");
		}
	}


}
/*
void sensortest()
{
//	unsigned char i,sensor;
	enable_timer1(10000);
	
   LCDClear();
   _delay_ms(50);

   while(1)
   {
     sense1();
	 LCD(3,0,"LF");

     LCD(7,0,"LB");

     LCD(11,0,"SF");

     LCD(15,0,"SB");
	 

  	 if(chk(PINA,0))
		      {
		        LCD(5,0,"1");
		      }
		       else
		      {
		        LCD(5,0,"0");
		      }

		   
		   
		  
      if(chk(PINA,1))
		      {
		       LCD(9,0,"1");
		      }
		       else
		      {
		        LCD(9,0,"0");
		      }

	  if(chk(PIND,4))
		      {
		       LCD(13,0,"1");
		      }
		       else
		      {
		        LCD(13,0,"0");
		      }
	  if(chk(PIND,7))
		      {
		       LCD(17,0,"1");
		      }
		       else
		      {
		        LCD(17,0,"0");
		      }
		       
	 LCD(9,1,"A");

     LCD(11,1,"B");

     LCD(13,1,"C");

     LCD(15,1,"D");
	 
	 LCD(1,2,"CTR");

	 
	 if(chk(PIND,0))
		      {
		        LCD(10,1,"1");
		      }
		       else
		      {
		        LCD(10,1,"0");
		      }

		   
		   
		  
    if(chk(PIND,1))
		      {
		       LCD(12,1,"1");
		      }
		       else
		      {
		        LCD(12,1,"0");
		      }

	if(chk(PIND,2))
		      {
		       LCD(14,1,"1");
		      }
		       else
		      {
		        LCD(14,1,"0");
		      }
	if(chk(PIND,3))
		      {
		       LCD(16,1,"1");
		      }
		       else
		      {
		        LCD(16,1,"0");
		      }
	if(chk(PIND,5))
		      {
		        LCD(4,2,"1");
		      }
		       else
		      {
		        LCD(4,2,"0");
		      }
	
	LCDvar(10,3,TCNT1,5);
			  
			  LCD(0,3,"wl");

			  LCD(4,3,"wr");
	if(chk(PINA,2))
		      {
		       LCD(6,3,"1");
		      }
		       else
		      {
		        LCD(6,3,"0");
		      }
	if(chk(PINA,4))
		      {
		       LCD(2,3,"1");
		      }
		       else
		      {
		        LCD(2,3,"0");
		      }
		  
   }
   
}*/
