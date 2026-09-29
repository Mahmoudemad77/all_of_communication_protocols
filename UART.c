#include <avr/io.h>
#include "UART.h"
#include "BIT_MATH.h"
#define F_CPU 16000000UL
void UART_INIT(u16 baud_rate) 
{
  u16 ubrr;
  
  CLR_BIT(DDRD , PD0); // to make RX input
  SET_BIT(DDRD , PD1);// to make TX output
  
  ubrr =(F_CPU / (16UL * baud_rate)) -1;
  
  UBRR0H = (u8)(ubrr >> 8);
  UBRR0L = (u8)ubrr;
  // to enable transmitter and receiver 
  SET_BIT(UCSR0B, RXEN0);
  SET_BIT(UCSR0B, TXEN0);
   // to make 8 bits of data and 1 stop bit --------(8N1)------
  SET_BIT(UCSR0C, UCSZ01);
  SET_BIT(UCSR0C, UCSZ00);

  
}


void UART_send_char(u8 data)
{
 /* Wait until transmit buffer is empty */
 while (GET_BIT(UCSR0A, UDRE0) == 0);
 UDR0 = data;	
}

void UART_send_string(const char *str)
{
	while(*str != '\0')
	{
		UART_send_char(*str);
		str++;
	}
}

u8 UART_Recive_Char(void)
{
	while(GET_BIT(UCSR0A , RXC0) == 0);
	return	UDR0;
}

void UART_send_hex(u8 data)
{
	const char hex[] = "123456789ABCDEF";
	
	UART_send_char(hex[(data >> 4) & 0x0F]);
	UART_send_char(hex[data & 0x0F]);
}