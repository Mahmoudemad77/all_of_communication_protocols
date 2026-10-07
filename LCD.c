#include "LCD.h"
#include "I2C.h"

#include <util/delay.h>
#include <stdlib.h>


/* =========================================================
   PCF8574 WRITE
   ========================================================= */

static void PCF8574_Write(uint8_t data)
{
    I2C_Start_condition();

    I2C_Send_SLA_W(LCD_I2C_ADDRESS);

    I2C_Write(data);

    I2C_Stop();
}


/* =========================================================
   SEND 4 BITS TO LCD
   ========================================================= */

static void LCD_Send4Bits(uint8_t data, uint8_t rs)
{
    uint8_t value = 0;

    /*
     * Put LCD data on P4-P7
     *
     * data:
     * P4 = D4
     * P5 = D5
     * P6 = D6
     * P7 = D7
     */

    value |= (data & 0x0F) << 4;


    /* RS */

    if (rs)
    {
        value |= (1 << LCD_RS);
    }


    /* Backlight ON */

    value |= (1 << LCD_BL);


    /* Send data with EN = 0 */

    PCF8574_Write(value);


    /* EN = 1 */

    value |= (1 << LCD_EN);

    PCF8574_Write(value);

    _delay_us(1);


    /* EN = 0 */

    value &= ~(1 << LCD_EN);

    PCF8574_Write(value);

    _delay_us(100);
}


/* =========================================================
   SEND FULL BYTE
   ========================================================= */

static void LCD_Send(uint8_t data, uint8_t rs)
{
    /* High nibble */

    LCD_Send4Bits(data >> 4, rs);


    /* Low nibble */

    LCD_Send4Bits(data & 0x0F, rs);
}


/* =========================================================
   LCD COMMAND
   ========================================================= */

void LCD_Command(uint8_t command)
{
    /*
     * RS = 0
     */

    LCD_Send(command, 0);

    _delay_ms(2);
}


/* =========================================================
   LCD CHARACTER
   ========================================================= */

void LCD_Char(char data)
{
    /*
     * RS = 1
     */

    LCD_Send((uint8_t)data, 1);

    _delay_us(100);
}


/* =========================================================
   LCD STRING
   ========================================================= */

void LCD_String(char *str)
{
    while (*str)
    {
        LCD_Char(*str);
        str++;
    }
}


/* =========================================================
   LCD CLEAR
   ========================================================= */

void LCD_Clear(void)
{
    LCD_Command(0x01);

    _delay_ms(2);
}


/* =========================================================
   LCD SET CURSOR
   ========================================================= */

void LCD_SetCursor(uint8_t row, uint8_t col)
{
    if (row == 0)
    {
        LCD_Command(0x80 + col);
    }
    else
    {
        LCD_Command(0xC0 + col);
    }
}


/* =========================================================
   LCD NUMBER
   ========================================================= */

void LCD_Number(int32_t number)
{
    char buffer[12];

    ltoa(number, buffer, 10);

    LCD_String(buffer);
}


/* =========================================================
   LCD INITIALIZATION
   ========================================================= */

void LCD_Init(void)
{
    /*
     * Wait for LCD power-up
     */

    _delay_ms(20);


    /*
     * Initialization sequence
     *
     * LCD starts in 8-bit mode
     * then we switch to 4-bit mode
     */

    LCD_Send4Bits(0x03, 0);

    _delay_ms(5);


    LCD_Send4Bits(0x03, 0);

    _delay_us(150);


    LCD_Send4Bits(0x03, 0);

    _delay_us(150);


    /*
     * Switch to 4-bit mode
     */

    LCD_Send4Bits(0x02, 0);

    _delay_ms(1);


    /*
     * Function Set
     *
     * 4-bit
     * 2 lines
     * 5x8 font
     */

    LCD_Command(0x28);


    /*
     * Display ON
     * Cursor OFF
     * Blink OFF
     */

    LCD_Command(0x0C);


    /*
     * Clear Display
     */

    LCD_Command(0x01);

    _delay_ms(2);


    /*
     * Entry Mode
     *
     * Cursor moves right
     */

    LCD_Command(0x06);
}