#include "uart.h"

void uart_init() {
	// Set baud rate
	UBRRL = (unsigned char)(BAUD_PRESCALE & 0xFF);
	UBRRH = (unsigned char)(BAUD_PRESCALE >> 8);
	// rx and tx
	UCSRB = (1<<RXEN)|(1<<TXEN);
	// 8bit data, no parity, 1bit stop
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
}


void uart_tx_byte(char c) {
	while((UCSRA&(1<<UDRE)) == 0);
	UDR = c;
}


unsigned char uart_available() {
	return (UCSRA &(1<<RXC));
}


unsigned char uart_wait_rx() {
	while( uart_available() == 0 );
	return UDR;
}


void uart_tx_string(char *str) {
	while(*str) {
		uart_tx_byte(*str);
		str++;
	}
}
