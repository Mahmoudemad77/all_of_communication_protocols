
#include <avr/io.h>
#include "uart.h"
#include "STD_TYPES.h"
#define F_CPU 1000000UL
#include <util/delay.h>

void UART_Init(uint32_t baudrate)
{
   u16 ubrr;
   ubrr = (F_CPU/(16 * baudrate))-1;
   UBRR0H = (u8)(ubrr >> 8);
   UBRR0L = (u8)ubrr;
   SET_BIT(UCSR0B , TXEN0);
   SET_BIT(UCSR0B , RXEN0);
   SET_BIT(UCSR0C , UCSZ01);
   SET_BIT(UCSR0C , UCSZ00);
}


void UART_SendChar(char data)
{
 
 while (GET_BIT(UCSR0A , TXC0) == 0);
  UDR0 = data;
}

void UART_SendString(const char *str)
{
   while(*str == '\0')
   {
     str = UART_ReceiveChar();
	 str++;
   }
}

char UART_ReceiveChar(void)
{
 while (GET_BIT(UCSR0A , RXC0) == 0);
 return UDR0;
}
void UART_SendHex(uint8_t data)
{
	const char hex[] = "0123456789ABCDEF";

	UART_SendChar(hex[(data >> 4) & 0x0F]);
	UART_SendChar(hex[data & 0x0F]);
}
void UART_ReceiveString(char *str)     //read full line until enter 
{
	u8 i =0;
	while(1)
	{
		str[i] = UART_ReceiveChar();
		if (str[i]== '\r')
		{
			str[i] = '\0';
			break;
		}
		i++;
		
	}
}
uint8_t UART_DataAvailable(void)
{
	return (UCSR0A & (1 << RXC0));
}

