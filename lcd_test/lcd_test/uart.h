/*
 * uart.h
 *
 * Created: 1/1/2013 2:37:19 PM
 *  Author: Pranav
 */ 


#ifndef UART_H_
#define UART_H_

void uart_0_ini();
void uart_1_ini();
void uart_0_Transmit(unsigned char data);
void uart_1_Transmit(unsigned char data);
void stringuart0(char*string);
void stringuart1(char*string);
unsigned char USART1_Recieve();
void uartWriteInt(int val,unsigned int field_length);
#endif /* UART_H_ */