#ifndef UART_H
#define UART_H
#include "STD_TYPES.h"

void UART_INIT(u16 baud_rate); // to init uart 


void UART_send_char(u8 data); // to send one letter 
void UART_send_string(const char *str); // to send word 
u8 UART_Recive_Char(void); // to recive word or letter
void UART_send_hex(u8 data); // to send hex number 
#endif