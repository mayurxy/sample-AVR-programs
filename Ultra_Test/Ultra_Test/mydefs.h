#ifndef MYUTILS_H
 #define MYUTILS_H

 #define _CONCAT(a,b) a##b
 #define PORT(x) _CONCAT(PORT,x)
 #define PIN(x) _CONCAT(PIN,x)
 #define DDR(x) _CONCAT(DDR,x)

	#define set(a,b) a|=(1<<b)
	#define clr(a,b) a&=(~(1<<b))
	#define chk(a,b) a&(1<<b)	

/************mode selections**********/

#define window 15

#define Init_LED() {\
set(DDRG,0);\
set(DDRG,1);\
set(DDRG,2);\
set(DDRG,4);\
set(DDRC,0);\
}


//#define input_port_1 PIND
//#define input_port_2 PINF


#define glow1() set(PORTG,0);
#define off1() 	clr(PORTG,0);

#define glow2() set(PORTG,1);
#define off2() 	clr(PORTG,1);

#define glow3() set(PORTG,2);
#define off3() 	clr(PORTG,2);

#define glow4() set(PORTG,4);
#define off4() 	clr(PORTG,4);

#define reset_glow() set(PORTC,0);
#define reset_off() clr(PORTC,0);

//#define Init_lift_lock() {\
//set(DDRE,1);\
//}

//#define unlock() set(PORTE,1);
//#define lock() clr(PORTE,1);

#define m1_port    E
#define m1_1   	   3
#define m1_2       5

#define m2_port    E
#define m2_1       4
#define m2_2       2

/*#define m3_port  A
#define m3_1       4
#define m3_2       7

#define m4_port    A
#define m4_1       0
#define m4_2       1

#define m6_port    C
#define m6_1       3
#define m6_2       5

#define m7_port    C
#define m7_1       4
#define m7_2       2

#define m8_port    C
#define m8_1       6
#define m8_2       7*/


#define m1_p    PORT(m1_port)
#define m2_p    PORT(m2_port)
/*#define m3_p    PORT(m3_port)
#define m4_p    PORT(m4_port)
#define m6_p    PORT(m6_port)
#define m7_p    PORT(m7_port)
#define m8_p    PORT(m8_port)*/


#define m1_d    DDR(m1_port)
#define m2_d    DDR(m2_port)
/*#define m3_d    DDR(m3_port)
#define m4_d    DDR(m4_port)
#define m6_d    DDR(m6_port)
#define m7_d    DDR(m7_port)
#define m8_d    DDR(m8_port)*/


//#define InitMotors() {\
//set(m1_d,m1_1);\
//set(m2_d,m2_1);\
//}






#endif
