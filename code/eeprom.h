#ifndef EEPROM_H_
#define EEPROM_H_

#include <avr/io.h>
#include <util/delay.h>

#define PIN_SCLK	(1<<2) // PD2: Shift Register Serial Clock
#define PIN_LATCH	(1<<3) // PD3: Shift Register RClock
#define PIN_SDAT	(1<<4) // PD4: Shift Register Serial Data
#define PIN_WR		(1<<5) // PD5: EEPROM Write Enable (active low)
#define PIN_RD		(1<<6) // PD6: EEPROM Read Enable (active low)
#define PIN_LED		(1<<7) // PD7: Status LED


void eeprom_init();

void databus_input();
void databus_output();

void databus_set(unsigned char data);
unsigned char databus_get();

void addrbus_set(unsigned short addr);

void eeprom_write(unsigned short addr, unsigned char data);
unsigned char eeprom_write_validate(unsigned short addr, unsigned char data);
unsigned char eeprom_read(unsigned short addr);

void eeprom_disable_protect();

#endif