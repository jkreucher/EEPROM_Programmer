#include "uart.h"
#include "eeprom.h"
#include "parser.h"


char help_text[] =
"EEPROM PROGRAMMER v1.1\r\n"
"**********************\r\n"
"by Jannik Kreucher\r\n\n"
"h         - Help\r\n"
"d         - Disable write protect\r\n"
"w AAAA DD - Write to EEPROM\r\n"
"r AAAA    - Read from EEPROM\r\n"
"return: Byte in EEPROM\r\n"
"Everything in hex format!\r\n\n";


int main() {
	// some setup stuff
	eeprom_init();
	uart_init();

	uart_tx_string(help_text);	

	// uart rx char, data for eeprom
	unsigned char c, data;
	unsigned short address;

	while(1) {
		// first command character
		c = uart_wait_rx();

		// help text
		if(c == 'h') {
			PORTD |= PIN_LED;
			uart_tx_string(help_text);
			PORTD &= ~PIN_LED;
		}
		// disable write protect
		else if(c == 'd') {
			eeprom_disable_protect();
			uart_tx_byte('d');
		}
		// write to eeprom
		else if(c == 'w') {
			address = parse_byte();                  // higher byte first
			address = (address << 8) | parse_byte(); // then lower byte
			data    = parse_byte();                  // now data
			// write to eeprom
			data = eeprom_write_validate(address, data);
			// send written data back via uart
			uart_tx_byte( bin_to_hex( data >> 4 ) );
			uart_tx_byte( bin_to_hex( data ) );
		}
		// read from eeprom
		else if(c == 'r') {
			address = parse_byte();                  // higher byte first
			address = (address << 8) | parse_byte(); // then lower byte
			// read from eeprom
			data = eeprom_read(address);
			// send back via uart
			uart_tx_byte( bin_to_hex( data >> 4 ) );
			uart_tx_byte( bin_to_hex( data ) );
		}

	}

	return 0;
}
