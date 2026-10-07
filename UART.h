#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include <util/delay.h>

void UART_Init(uint32_t baudrate);

void UART_SendChar(char data);
void UART_SendString(const char *str);
void UART_SendHex(uint8_t data);
char UART_ReceiveChar(void);
void UART_ReceiveString(char *str);
uint8_t UART_DataAvailable(void);
#endif /* UART_H_ */