#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

/* I2C Status */
#define I2C_OK              1
#define I2C_ERROR           0

/* I2C Functions */

void I2C_Master_Init(void);

uint8_t I2C_Start_condition(void);

uint8_t I2C_Send_SLA_W(uint8_t address);

uint8_t I2C_Send_SLA_R(uint8_t address);

uint8_t I2C_Write(uint8_t data);

uint8_t I2C_Read_ACK(void);

uint8_t I2C_Read_NACK(void);

void I2C_Stop(void);

uint8_t I2C_Repeated_Start(void);

/* Slave */

void I2C_Slave_Init(uint8_t address);

uint8_t I2C_Slave_Receive(void);

uint8_t I2C_Probe(uint8_t address);




#endif