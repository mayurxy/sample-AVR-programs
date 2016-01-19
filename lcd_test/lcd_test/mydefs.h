#ifndef MYUTILS_H
 #define MYUTILS_H

 #define _CONCAT(a,b) a##b
 #define PORT(x) _CONCAT(PORT,x)
 #define PIN(x) _CONCAT(PIN,x)
 #define DDR(x) _CONCAT(DDR,x)

	#define set(a,b) a|=(1<<b)
	#define clr(a,b) a&=(~(1<<b))
	#define chk(a,b) a&(1<<b)	


#define Init_LED() {\
set(DDRG,0);\
set(DDRG,1);\
set(DDRG,2);\
set(DDRG,3);\
}

#define glow1() set(PORTG,0);
#define off1() 	clr(PORTG,0);

#define glow2() set(PORTG,1);
#define off2() 	clr(PORTG,1);

#define glow3() set(PORTG,2);
#define off3() 	clr(PORTG,2);

#define glow4() set(PORTG,3);
#define off4() 	clr(PORTG,3);




#endif
