/*
 * encoder_maxon.h
 *
 * Created: 11-08-2012 PM 12:49:00
 *  Author: Pranav
 */ 



#ifndef ENCODER_MAXON_H_
#define ENCODER_MAXON_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#ifndef F_CPU
	#define F_CPU 16000000UL
#endif

#include "mydefs.h"

volatile unsigned int maxon1=0;

void ini_maxon_enco(unsigned int steps);
void init_encoder()
{
	clr(DDRE,6);
	TCCR3A=0;
 TCCR3B=(1<<WGM32)|(1<<CS32)|(1<<CS30) |(1<<CS31);
 ETIMSK|=(1<<OCIE3A);
 TCNT3=0;
}


void ini_maxon_enco(unsigned int steps)
{
 
 TCNT3=0;
 OCR3A=steps;
 maxon1=0;

}

ISR(TIMER3_COMPA_vect)
{
	maxon1++;
}

#endif /* ENCODER_MAXON_H_ */
