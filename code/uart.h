#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

#define BAUD 115200ul
#define BAUD_PRESCALE ((F_CPU/(BAUD*16ul))-1)

void uart_init();
void uart_tx_byte(char c);
unsigned char uart_available();
unsigned char uart_wait_rx();
void uart_tx_string(char *str);

#endif