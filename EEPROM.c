
#include "EEPROM.h"
#include "I2C.h"
 #define F_CPU 1000000
#include <util/delay.h>


/* Write one byte */                                   //0b0000 0 A2 A3 A0 LOCATION
void EEPROM_Write(uint16_t address, uint8_t data)      //0b0000 0  1  1  0 1111 1111 
{ 
	/* START */ 
	I2C_Start_condition();

	/* SLA + W */
	I2C_Send_SLA_W(0b01010000|(address>>8));    //0b00000  1  1  0
	                                            //0b01010  0  0  0          |
                                                          
	/* EEPROM memory address */
	I2C_Write((uint8_t)address); 

	/* Data */
	I2C_Write(data);

	/* STOP */
	I2C_Stop();
	_delay_ms(5);
	
}


/* Read one byte */
uint8_t EEPROM_Read(uint16_t address)
{
	uint8_t data;

	/* START */
	I2C_Start_condition();

	/* SLA + W */
	I2C_Send_SLA_W(0b1010000|(address>>8));

	/* Send memory address */
	I2C_Write((uint8_t)address);

	/* Repeated START */
	I2C_Repeated_Start();

	/* SLA + R */
	I2C_Send_SLA_R(0b1010000|(address>>8));

	/* Read data + NACK */
	data = I2C_Read_NACK();

	/* STOP */
	I2C_Stop();
	_delay_ms(5);
	
	return data;
}
