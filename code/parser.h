#ifndef PARSER_H_
#define PARSER_H_

#include "uart.h"

unsigned char hex_to_bin(char c);
char bin_to_hex(unsigned char data);

unsigned char parse_byte();

#endif