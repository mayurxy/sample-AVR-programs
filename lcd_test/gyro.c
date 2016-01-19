#include <avr/io.h>
#ifndef F_CPU
	#define F_CPU 16000000UL
#endif

#define left 1
#define right 4  //4
#define back 2//2
#define front 3 //3
 
#define ADXL345_W	0b00111010
#define ADXL345_R	0b00111011

#define FALSE	0
#define TRUE	-1

#include <util/delay.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include "gyro.h"
#include "lcd.h"
#include "hmc.h"
#include "pwm.h"
#include "i2c.h"
#include "types.h"
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

   volatile float Q_angle; // Process noise variance for the accelerometer
   volatile float Q_bias; // Process noise variance for the gyro bias
   volatile float R_measure; // Measurement noise variance - this is actually the variance of the measurement noise
    /////////////////////////////////////////////////////////////////////
   volatile float Xangle; // The angle calculated by the Kalman filter - part of the 2x1 state matrix
   volatile float Xbias; // The gyro bias calculated by the Kalman filter - part of the 2x1 state matrix
   volatile float Xrate; // Unbiased rate calculated from the rate and the calculated bias - you have to call getAngle to update the rate
    
   volatile float XP[2][2]; // Error covariance matrix - This is a 2x2 matrix
   volatile float XK[2]; // Kalman gain - This is a 2x1 matrix
   volatile float Xy; // Angle difference - 1x1 matrix
   volatile float XS; // Estimate error - 1x1 matrix
///////////////////////////////////////////////////////////////////////////////
   volatile float Yangle; // The angle calculated by the Kalman filter - part of the 2x1 state matrix
   volatile float Ybias; // The gyro bias calculated by the Kalman filter - part of the 2x1 state matrix
   volatile float Yrate; // Unbiased rate calculated from the rate and the calculated bias - you have to call getAngle to update the rate
    
   volatile float YP[2][2]; // Error covariance matrix - This is a 2x2 matrix
   volatile float YK[2]; // Kalman gain - This is a 2x1 matrix
   volatile float Yy; // Angle difference - 1x1 matrix
   volatile float YS; // Estimate error - 1x1 matrix

volatile long int ch1time=0,ch1on=0,ch2time=0,ch2on=0,ch3time=0,ch3on=0,ch4time=0,ch4on=0,ch1tmp=0,ch2tmp=0,ch3tmp=0,ch4tmp=0,task=0;
   int16_t read_adxl345(char reg_adr);
   
   
ISR(TIMER2_COMP_vect)
{

	int16_t x, y, z;
 TIMSK&=~(1<<OCIE2);
 sei();
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
	
///0.925ms+
//Z_angle=(float)Z_angle+((float)Z_Data*0.07*0.00768);

//X_angle=(float)X_angle+((float)X_Data*0.07*0.00768);
//Y_angle=(float)Y_angle+((float)Y_Data*0.07*0.00768);

//Y_angle=(float)Y_angle+((float)Y_Data*0.07*0.00192);
//if(counter == 200)
//**********************************//
  
  if (counteracc==10)
  {
  
	x = read_adxl345(0x32);
		y = read_adxl345(0x34);
		z = read_adxl345(0x36);
		
		xacc = (float)x/256;
		yacc = (float)y/256;
		zacc = (float)z/256;

		xangle=(atan(xacc/sqrt(yacc*yacc+zacc*zacc))*180/3.14)*-1;
		yangle=(atan(yacc/sqrt(xacc*xacc+zacc*zacc))*180/3.14)*-1;
		zangle=atan(sqrt(xacc*xacc+yacc*yacc)/zacc)*180/3.14;
		counteracc=0;
  }		


Xangle=0.98*(Xangle+(float)X_Data*0.07*0.00768)+0.02*(yangle);
Yangle=0.98*(Yangle+(float)Y_Data*0.07*0.00768)+0.02*(xangle);

//Y_angle=Yangle;
//X_angle=Xangle;

		//X_angle=(-1)*yangle;
 //Y_angle=xangle;


//**************** Kalman  ******************//
//Yangle=YgetAngle(xangle,Y_Data*0.07,0.00768);
		
//Yangle=YgetAngle(xangle,Y_Data*0.07,0.00768);

//Xangle=XgetAngle((-1)*yangle,X_Data*0.07,0.00768);



//Xangle=XgetAngle((-1)*yangle,X_Data*0.07,0.00768);
//counter=0;




//Y_new_angle=0.98*Y_angle+0.02*xangle;
//X_new_angle=0.98*X_angle+0.02*(-1)*yangle;
//
temp=TCNT2;

if (counter == 200&&counterz>=1)
{
		Z_angle_mag_current = HMC();
	
	counter=0;
	
	set1=Z_angle_mag_current-Z_angle_mag;
if(set1<0)
set1=set1+360;
if((set1<360)&&(set1>180))
set1=set1-360;
Z_angle=(-1)*set1;

	
}
if (counterz==0)
{
	//Z_angle_mag = HMC();
	counterz++;
	
}


TCNT2=temp;

//X_angle=(float)X_angle+((float)X_Data*0.07*0.00192);
//apna_angle=(float)apna_angle+((float)Z_Data*8.75 *0.002*0.000925);
counter++;
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


//Z_angle_mag_current = HMC();
//Z_angle_mag_current = Z_angle_mag_current-Z_angle_mag;
TIMSK|=1<<OCIE2;
 
}
 
int16_t read_adxl345(char reg_adr)
{		
	char lsb, msb;

	i2cSendStart();
	i2cWaitForComplete();
	
	i2cSendByte(ADXL345_W);	// write to this I2C address, R/*W cleared
	i2cWaitForComplete();
	
	i2cSendByte(reg_adr);	//Read from a given address
	i2cWaitForComplete();
	
	i2cSendStart();
	
	i2cSendByte(ADXL345_R); // read from this I2C address, R/*W Set
	i2cWaitForComplete();
	
	i2cReceiveByte(TRUE);
	i2cWaitForComplete();
	lsb = i2cGetReceivedByte(); //Read the LSB data
	i2cWaitForComplete();

	i2cReceiveByte(FALSE);
	i2cWaitForComplete();
	msb = i2cGetReceivedByte(); //Read the MSB data
	i2cWaitForComplete();
	
	i2cSendStop();
	
	return( (msb<<8) | lsb);
}

//Setup ADXL345 for constant measurement mode
void init_adxl345(void)
{
	i2cSendStart();
	i2cWaitForComplete();

	i2cSendByte(ADXL345_W); //write to ADXL345
	i2cWaitForComplete();

	i2cSendByte(0x2D); //Write to Power CTL register
	i2cWaitForComplete();

	i2cSendByte( (1<<3) ); //Set the measure bit on D3
	i2cWaitForComplete();

	i2cSendStop();
}

 void cleargyro(void)
 {
	 int i=0;
	 X_mean=0;
	 Y_mean=0;
	 
 }
/////////////////Functions/////////////////////////////////
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
		init_adxl345();
	
	
InitRead();
Z_angle_mag=HMC();

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


void kalmaninit(void)
{
	        /* We will set the varibles like so, these can also be tuned by the user */
        Q_angle = 0.001;
        Q_bias = 0.003;
        R_measure = 0.03;
        
        
        XP[0][0] = 0; // Since we assume tha the bias is 0 and we know the starting angle (use setAngle), the error covariance matrix is set like so - see: http://en.wikipedia.org/wiki/Kalman_filter#Example_application.2C_technical
        XP[0][1] = 0;
        XP[1][0] = 0;
        XP[1][1] = 0;
		
   	    YP[0][0] = 0; // Since we assume tha the bias is 0 and we know the starting angle (use setAngle), the error covariance matrix is set like so - see: http://en.wikipedia.org/wiki/Kalman_filter#Example_application.2C_technical
        YP[0][1] = 0;
        YP[1][0] = 0;
        YP[1][1] = 0;

		Xbias=X_zero;
		Ybias=Y_zero;

}


	void setQangle(float newQ_angle) { Q_angle = newQ_angle; };
    void setQbias(float newQ_bias) { Q_bias = newQ_bias; };
    void setRmeasure(float newR_measure) { R_measure = newR_measure; };
    
    float getQangle() { return Q_angle; };
    float getQbias() { return Q_bias; };
    float getRmeasure() { return R_measure; };
		
	float XgetAngle(float newAngle, float newRate, float dt) {
        // KasBot V2  -  Kalman filter module - http://www.x-firm.com/?page_id=145
        // Modified by Kristian Lauszus
        // See my blog post for more information: http://blog.tkjelectronics.dk/2012/09/a-practical-approach-to-kalman-filter-and-how-to-implement-it
                        
        // Discrete Kalman filter time update equations - Time Update ("Predict")
        // Update xhat - Project the state ahead
        /* Step 1 */
        Xrate = newRate - Xbias;
        Xangle += dt * Xrate;
        
        // Update estimation error covariance - Project the error covariance ahead
        /* Step 2 */
        XP[0][0] += dt * (dt*XP[1][1] - XP[0][1] - XP[1][0] + Q_angle);
        XP[0][1] -= dt * XP[1][1];
        XP[1][0] -= dt * XP[1][1];
        XP[1][1] += Q_bias * dt;
        
        // Discrete Kalman filter measurement update equations - Measurement Update ("Correct")
        // Calculate Kalman gain - Compute the Kalman gain
        /* Step 4 */
        XS = XP[0][0] + R_measure;
        /* Step 5 */
        XK[0] = XP[0][0] / XS;
        XK[1] = XP[1][0] / XS;
        
        // Calculate angle and bias - Update estimate with measurement zk (newAngle)
        /* Step 3 */
        Xy = newAngle - Xangle;
        /* Step 6 */
        Xangle += XK[0] * Xy;
        Xbias += XK[1] * Xy;
        
        // Calculate estimation error covariance - Update the error covariance
        /* Step 7 */
        XP[0][0] -= XK[0] * XP[0][0];
        XP[0][1] -= XK[0] * XP[0][1];
        XP[1][0] -= XK[1] * XP[0][0];
        XP[1][1] -= XK[1] * XP[0][1];
        
        return Xangle;

		
    };
	
	
	float YgetAngle(float newAngle, float newRate, float dt) {
        // KasBot V2  -  Kalman filter module - http://www.x-firm.com/?page_id=145
        // Modified by Kristian Lauszus
        // See my blog post for more information: http://blog.tkjelectronics.dk/2012/09/a-practical-approach-to-kalman-filter-and-how-to-implement-it
                        
        // Discrete Kalman filter time update equations - Time Update ("Predict")
        // Update xhat - Project the state ahead
        /* Step 1 */
        Yrate = newRate - Ybias;
        Yangle += dt * Yrate;
        
        // Update estimation error covariance - Project the error covariance ahead
        /* Step 2 */
        YP[0][0] += dt * (dt*YP[1][1] - YP[0][1] - YP[1][0] + Q_angle);
        YP[0][1] -= dt * YP[1][1];
        YP[1][0] -= dt * YP[1][1];
        YP[1][1] += Q_bias * dt;
        
        // Discrete Kalman filter measurement update equations - Measurement Update ("Correct")
        // Calculate Kalman gain - Compute the Kalman gain
        /* Step 4 */
        YS = YP[0][0] + R_measure;
        /* Step 5 */
        YK[0] = YP[0][0] / YS;
        YK[1] = YP[1][0] / YS;
        
        // Calculate angle and bias - Update estimate with measurement zk (newAngle)
        /* Step 3 */
        Yy = newAngle - Yangle;
        /* Step 6 */
        Yangle += YK[0] * Yy;
        Ybias += YK[1] * Yy;
        
        // Calculate estimation error covariance - Update the error covariance
        /* Step 7 */
        YP[0][0] -= YK[0] * YP[0][0];
        YP[0][1] -= YK[0] * YP[0][1];
        YP[1][0] -= YK[1] * YP[0][0];
        YP[1][1] -= YK[1] * YP[0][1];
        
        return Yangle;

		
    };	
	