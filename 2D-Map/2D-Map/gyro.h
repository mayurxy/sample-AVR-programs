#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include <avr/interrupt.h>

void TWI_start(void);
void disable_gyro();
void TWI_repeated_start(void);
void TWI_init_master(void);
void TWI_write_address(unsigned char);
void TWI_read_address(unsigned char);
void TWI_write_data(unsigned char);
unsigned char TWI_read_data(void);
void TWI_stop(void);
signed short int getdata(unsigned char add);

