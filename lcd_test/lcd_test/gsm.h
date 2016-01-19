/*
 * gsm.h
 *
 * Created: 1/1/2013 8:25:56 PM
 *  Author: Pranav
 */ 


#ifndef GSM_H_
#define GSM_H_
unsigned char checkok();
unsigned char sms(unsigned char *number,unsigned char *msg);
unsigned char call(unsigned char *number);



#endif /* GSM_H_ */