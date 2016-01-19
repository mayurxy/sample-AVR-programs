/*
 * MyDefs.h
 *
 * Created: 17-05-2012 AM 03:38:53
 *  Author: Aniket
 */ 


#ifndef MYDEFS_H_
#define MYDEFS_H_


 #define _CONCAT(a,b) a##b
 #define PORT(x) _CONCAT(PORT,x)
 #define PIN(x) _CONCAT(PIN,x)
 #define DDR(x) _CONCAT(DDR,x)

	#define set(a,b) a|=(1<<b)
	#define clr(a,b) a&=(~(1<<b))
	#define chk(a,b) a&(1<<b)

	/***********leds*********************/
	
#define glow1() set(PORTG,2);
#define off1() 	clr(PORTG,2);

#define glow2() set(PORTG,4);
#define off2() 	clr(PORTG,4);

#define glow3() set(PORTG,1);
#define off3() 	clr(PORTG,1);

#define glow4() set(PORTG,0);
#define off4() 	clr(PORTG,0);

void init_motors();
void run_motors(int, int, int);
void line_trace(uint8_t);

#endif /* MYDEFS_H_ */