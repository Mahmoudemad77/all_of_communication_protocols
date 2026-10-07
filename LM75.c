#include "LM75.h"
#include "I2C.h"
uint8_t LM75_ReadTemperature(void)
{
	uint8_t high;
	uint8_t low;

	/* START */
	if (I2C_Start_condition() == I2C_ERROR)
	return 255;

	/* SLA + W */
	if (I2C_Send_SLA_W(LM75_ADDRESS) == I2C_ERROR)
	{
		I2C_Stop();
		return 255;
	}

	/* Temperature register */
	if (I2C_Write(0x00) == I2C_ERROR)
	{
		I2C_Stop();
		return 255;
	}

	/* Repeated START */
	if (I2C_Repeated_Start() == I2C_ERROR)
	{
		I2C_Stop();
		return 255;
	}

	/* SLA + R */
	if (I2C_Send_SLA_R(LM75_ADDRESS) == I2C_ERROR)
	{
		I2C_Stop();
		return 255;
	}

	/* MSB */
	high = I2C_Read_ACK();

	/* LSB */
	low = I2C_Read_NACK();

	I2C_Stop();

	return high;
}