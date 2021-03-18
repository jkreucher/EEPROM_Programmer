#include "eeprom.h"


/*** Default pin direction ***/
void eeprom_init() {
	// Control lines are outputs
	DDRD |= 0b11111100;
	// RD, WR high
	PORTD |= (PIN_RD | PIN_WR);
	// shift register pins low
	PORTD &= ~(PIN_SCLK | PIN_SDAT | PIN_LATCH);
	// databus input as default
	databus_input();
}


/*** Databus direction ***/
void databus_input() {
	DDRB = (DDRB & 0b11000000);
	DDRC = (DDRC & 0b11111100);
}

void databus_output() {
	DDRB = (DDRB | 0b00111111);
	DDRC = (DDRC | 0b00000011);
}


/*** Databus read/write ***/
void databus_set(unsigned char data) {
	databus_output();
	PORTB =  data & 0b00111111;
	PORTC = (data & 0b11000000) >> 6;
}

unsigned char databus_get() {
	databus_input();
	unsigned char data = 0;
	data = PINB & 0b00111111;
	data |= (PINC & 0b00000011) << 6;
	return data;
}


/*** Address Bus shift register stuff ***/
void addrbus_set(unsigned short addr) {
	// Latch, SCLK low (just to be sure)
	PORTD &= ~(PIN_SCLK | PIN_LATCH);

	// shift bits
	for(int i=0; i<16; i++) {
		// handle each data bit (msb first)
		if( ((addr << i) & 0x8000) == 0 ) {
			PORTD &= ~PIN_SDAT; // sdat low
		} else {
			PORTD |= PIN_SDAT; // sdat high
		}
		// shift data (rising edge)
		PORTD |= PIN_SCLK;
		PORTD &= ~PIN_SCLK;
	}

	// latch data to eeprom (rising edge)
	PORTD |= PIN_LATCH;
	PORTD &= ~PIN_LATCH;
}


/*** write data to eeprom ***/
void eeprom_write(unsigned short addr, unsigned char data) {
	// indicator led on
	PORTD |= PIN_LED;
	// save data to eeprom
	addrbus_set(addr);
	databus_set(data);
	// write data to eeprom (falling edge)
	PORTD &= ~PIN_WR;
	_delay_us(500);
	PORTD |= PIN_WR;
	_delay_us(500);
	// indicator led off
	PORTD &= ~PIN_LED;
}

unsigned char eeprom_write_validate(unsigned short addr, unsigned char data) {
	// check if byte is in eeprom already (save some write cycles)
	if(data == eeprom_read(addr)) { return data; }
	// save data to eeprom
	eeprom_write(addr, data);
	// validate written data
	return databus_get();
}

unsigned char eeprom_read(unsigned short addr) {
	// indicator led on
	PORTD |= PIN_LED;
	// get data from eeprom
	addrbus_set(addr);
	// we want high impedance before we enable read on eeprom
	databus_input();
	// read data now
	PORTD &= ~PIN_RD;
	unsigned char data = databus_get();
	PORTD |= PIN_RD;
	// indicator led off
	PORTD &= ~PIN_LED;
	return data;
}

void eeprom_disable_protect() {
	// for diable algorithm view datasheet
	eeprom_write(0x5555, 0xAA);
	eeprom_write(0x2AAA, 0x55);
	eeprom_write(0x5555, 0x80);
	eeprom_write(0x5555, 0xAA);
	eeprom_write(0x2AAA, 0x55);
	eeprom_write(0x5555, 0x20);
	// write protect disabled
}
