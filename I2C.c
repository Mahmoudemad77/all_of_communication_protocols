 #define F_CPU 1000000UL
#define SCL_FREQ 50000UL

#include <avr/io.h>
#include "I2C.h"


/* =========================================================
   MASTER INIT
   ========================================================= */

void I2C_Master_Init(void)
{
   TWSR = 0x00;
   TWBR = (F_CPU / SCL_FREQ + 16+2);
   
}


/* =========================================================
   START CONDITION
   ========================================================= */

uint8_t I2C_Start_condition(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|
	(1<<TWEN);
	
	while (!(TWCR & (1<<TWINT)));
}


/* =========================================================
   SEND SLA + WRITE
   ========================================================= */

uint8_t I2C_Send_SLA_W(uint8_t address)
{
	/*
     * 7-bit address
     *
     * address << 1
     *
     * R/W = 1 -> READ
     */

    TWDR = (address << 1) | 1;


    /*
     * Start transmission
     */

    TWCR = (1 << TWINT) |
           (1 << TWEN);


    /*
     * Wait
     */

    while (!(TWCR & (1 << TWINT)));


    /*
     * 0x40 =
     *
     * SLA+R transmitted
     * ACK received
     */

    if ((TWSR & 0xF8) == 0x40)
    {
        return I2C_OK;
    }

    return I2C_ERROR;
}
}


/* =========================================================
   SEND SLA + READ
   ========================================================= */

uint8_t I2C_Send_SLA_R(uint8_t address)
{
    /*
     * 7-bit address
     *
     * address << 1
     *
     * R/W = 1 -> READ
     */

    TWDR = (address << 1) | 1;


    /*
     * Start transmission
     */

    TWCR = (1 << TWINT) |
           (1 << TWEN);


    /*
     * Wait
     */

    while (!(TWCR & (1 << TWINT)));


    /*
     * 0x40 =
     *
     * SLA+R transmitted
     * ACK received
     */

    if ((TWSR & 0xF8) == 0x40)
    {
        return I2C_OK;
    }

    return I2C_ERROR;
}
/* =========================================================
   WRITE DATA
   ========================================================= */

uint8_t I2C_Write(uint8_t data)
{

}


/* =========================================================
   READ DATA + ACK
   ========================================================= */

uint8_t I2C_Read_ACK(void)
{
        /*
     * TWEA = 0
     *
     * After receiving data:
     * send NACK
     */

    TWCR = (1 << TWINT) |
	       (1 << TWEA)  |
           (1 << TWEN);


    /*
     * Wait
     */

    while (!(TWCR & (1 << TWINT)));


    /*
     * Return received data
     */

    return TWDR;
   

  
}


/* =========================================================
   READ DATA + NACK
   ========================================================= */

uint8_t I2C_Read_NACK(void)
{
    /*
     * TWEA = 0
     *
     * After receiving data:
     * send NACK
     */

    TWCR = (1 << TWINT) |
           (1 << TWEN);


    /*
     * Wait
     */

    while (!(TWCR & (1 << TWINT)));


    /*
     * Return received data
     */

    return TWDR;
}


/* =========================================================
   STOP CONDITION
   ========================================================= */

void I2C_Stop(void)
{
    /*
     * Generate STOP condition
     */

    TWCR = (1 << TWINT) |
           (1 << TWSTO) |
           (1 << TWEN);
}


/* =========================================================
   SLAVE INIT
   ========================================================= */

void I2C_Slave_Init(uint8_t address)
{
  
}


/* =========================================================
   SLAVE RECEIVE
   ========================================================= */

uint8_t I2C_Slave_Receive(void)
{
    /*
     * Enable TWI
     * Enable ACK
     * Clear TWINT
     */

    TWCR = (1 << TWINT) |
           (1 << TWEN) |
           (1 << TWEA);


    /*
     * Wait until something is received
     */

    while (!(TWCR & (1 << TWINT)));


    /*
     * Return received data
     */

    return TWDR;
}
uint8_t I2C_Repeated_Start(void)
{
   
}

uint8_t I2C_Probe(uint8_t address)
{
	uint8_t status;

	/* START */
	status = I2C_Start_condition();

	if (status == I2C_ERROR)
	{
		return I2C_ERROR;
	}

	/* SLA + WRITE */
	status = I2C_Send_SLA_W(address);

	/* STOP */
	I2C_Stop();

	return status;
}