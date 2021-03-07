#include "parser.h"


/*** string (hex val) to binary format conversion ***/
const char hex[16] = "fedcba9876543210";

unsigned char hex_to_bin(char c) {
	// read hex value
	unsigned char i=0;
	while(c != hex[i]) {
		// if reached the end we need to stop
		if(i >= 16) break;
		// next hex char
		i++;
	}
	return i;
}


char bin_to_hex(unsigned char data) {
	return hex[data & 0x0F];
}


/*** parse a byte from uart (in hex format) ***/
unsigned char parse_byte() {
	// local values
	unsigned char val=0, data=0, i=0;
	// read 2 hex values
	while(i<2) {
		// get char from uart
		val = hex_to_bin( uart_wait_rx() );
		// check if valid hex digit
		if(val < 16) {
			// is valid hex
			data |= val << (4*(1-i));
			// next hex digit
			i++;
		}
		// if not valid hex digit get another char
	}
	// return result
	return data;
}
