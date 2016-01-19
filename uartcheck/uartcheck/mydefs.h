
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
#define red 0x01
#define blue 0x02
#define stest 0x03
#define gyrtest1 0x04
#define turntest 0x05
#define gyrtest2 0x06
#define test 0x08
#define toofani 0x09
#define gyrswitch 0x0A
#define comm_test 0x0B
/*************Sine Cosine************/
//float cosine123[91]={1.0000,0.9998,0.9993,0.9986,0.9975,0.9961,0.9945,0.9925,0.9902,0.9876,0.9848,0.9816,0.9781,0.9743,0.9702,0.9659,0.9612,0.9563,0.9510,0.9455,0.9396,0.9335,0.9271,0.9205,0.9135,0.9063,0.8987,0.8910,0.8829,0.8746,0.8660,0.8571,0.8480,0.8386,0.8290,0.8191,0.8090,0.7986,0.7880,0.7771,0.7660,0.7547,0.7431,0.7313,0.7193,0.7071, 0.6947,0.6820,0.6691,0.6561,0.6428,0.6293,0.6157,0.6018,0.5878,0.5736,0.5592,0.5446,0.5299,0.5150,0.5000,0.4848,0.4695,0.4540,0.4384,0.4226,0.4067,0.3907,0.3746,0.3584,0.3420,0.3256,0.3090,0.2924,0.2756,0.2588,0.2419,0.2250,0.2079,0.1908,0.1736,0.1564,0.1392,0.1219,0.1045,0.0872,0.0698,0.0523,0.0349,0.0175,0.0000};


/*************Init Dip***************/
#define Initdip(){\
clr(DDRB,2);\
clr(DDRB,3);\
set(PORTB,2);\
set(PORTB,3);\
}

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

/**********motors***************/

#define m1_port_1    B  //OC1A
#define m1_port_2    C
#define m1_port_3    A
#define m1_1   	   5
#define m1_2       1
#define m1_3       0


#define m2_port_1    B  //OC1B
#define m2_port_2    A
#define m2_port_3    C
#define m2_1       6
#define m2_2       3
#define m2_3       0

#define m3_port_1    B  //OC1C
#define m3_port_2    A
#define m3_port_3    E
#define m3_1   	   7
#define m3_2       2
#define m3_3       2

#define m4_port_1    B   //OC0
#define m4_port_2    A
#define m4_port_3    E
#define m4_1       4
#define m4_2       1
#define m4_3       3

#define m1_p_1    PORT(m1_port_1)
#define m1_p_2    PORT(m1_port_2)
#define m1_p_3    PORT(m1_port_3)
#define m2_p_1    PORT(m2_port_1)
#define m2_p_2    PORT(m2_port_2)
#define m2_p_3    PORT(m2_port_3)
#define m3_p_1    PORT(m3_port_1)
#define m3_p_2    PORT(m3_port_2)
#define m3_p_3    PORT(m3_port_3)
#define m4_p_1    PORT(m4_port_1)
#define m4_p_2    PORT(m4_port_2)
#define m4_p_3    PORT(m4_port_3)

#define m1_d_1    DDR(m1_port_1)
#define m1_d_2    DDR(m1_port_2)
#define m1_d_3    DDR(m1_port_3)
#define m2_d_1    DDR(m2_port_1)
#define m2_d_2    DDR(m2_port_2)
#define m2_d_3    DDR(m2_port_3)
#define m3_d_1    DDR(m3_port_1)
#define m3_d_2    DDR(m3_port_2)
#define m3_d_3    DDR(m3_port_3)
#define m4_d_1    DDR(m4_port_1)
#define m4_d_2    DDR(m4_port_2)
#define m4_d_3    DDR(m4_port_3)




#define InitMotors() {\
set(m1_d_1,m1_1);\
set(m1_d_2,m1_2);\
set(m1_d_3,m1_3);\
set(m2_d_1,m2_1);\
set(m2_d_2,m2_2);\
set(m2_d_3,m2_3);\
set(m3_d_1,m3_1);\
set(m3_d_2,m3_2);\
set(m3_d_3,m3_3);\
set(m4_d_1,m4_1);\
set(m4_d_2,m4_2);\
set(m4_d_3,m4_3);\
}

/***********high level functions**********/

#define Init_switching_ports(){\
DDRA|=(1<<4)|(1<<5);\
}


#define switch_gyro_1(){\
clr(PORTA,5);\
}

#define switch_gyro_2(){\
set(PORTA,5);\
}

#define switch_fb_enco(){\
clr(PORTA,4);\
}

#define switch_rl_enco(){\
set(PORTA,4);\
}


/**************Init sensors************/

#define init_line_sensor(){\
DDRF=0;\
PORTF=0;\
}

/**********Communication*************/

#define init_comm(){\
set(DDRG,4);\
clr(PORTG,4);\
EICRB|=(1<<ISC71);\
EIMSK|=(1<<INT7);\
clr(DDRE,7);\
clr(DDRD,4);\
clr(DDRD,5);\
clr(DDRD,6);\
}
#define trigger_slave(){\
set(PORTG,4);\
_delay_ms(5);\
clr(PORTG,4);\
}

#endif
