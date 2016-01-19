/*
 * motors.h
 *
 * Created: 9/18/2012 7:01:06 PM
 *  Author: Bakshi
 */ 


#ifndef MOTORS_H_
#define MOTORS_H_

#define L2_grid INT5_vect
//#define R1_grid INT3_vect
#define L_grid INT4_vect
#define R_grid INT2_vect
//#define B_grid INT7_vect

#define f_motor 1
#define b_motor 2
#define l_motor 3
#define r_motor 4

void init_t0();
void init_t1();
void enable_int2();
void enable_int3();
void enable_int4();
void enable_int5();
void enable_int7();
void enable_interrupts();
void disable_int4();
void disable_int3();
void disable_int5();
void disable_int2();
void disable_int7();
void disable_interrupts();
void drive_mot(unsigned char mot_no,signed int speed);
void drive_fb(signed int l_speed, signed int r_speed);
void drive_lr(signed int l_speed, signed int r_speed);
void run_motors(int no ,int dir ,int pwm );
void send_com(uint8_t data);

#endif /* MOTORS_H_ */
