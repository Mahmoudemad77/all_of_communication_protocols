#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>

/* PCF8574 7-bit I2C address
 * Case Study address = 0x40 (8-bit)
 * Driver uses 7-bit address = 0x20
 */
#define LCD_I2C_ADDRESS    0x20

/* PCF8574 Pin Mapping */
#define LCD_RS             0
#define LCD_RW             1
#define LCD_EN             2
#define LCD_BL             3

#define LCD_D4             4
#define LCD_D5             5
#define LCD_D6             6
#define LCD_D7             7


/* LCD Functions */

void LCD_Init(void);

void LCD_Command(uint8_t command);

void LCD_Char(char data);

void LCD_String(char *str);

void LCD_Clear(void);

void LCD_SetCursor(uint8_t row, uint8_t col);

void LCD_Number(int32_t number);

#endif /* LCD_H_ */