
/*
 * CAT7 - Task 7A
 * 16x2 LCD Initialization and Character/String Display
 *
 * Controller : AT89S52
 * Compiler   : Keil C51
 * Crystal    : 11.0592 MHz
 * LCD        : HD44780-compatible 16x2
 * Interface  : 4-bit mode
 *
 * LCD Connections:
 * RS -> P2.0
 * RW -> P2.1
 * EN -> P2.2
 * D4 -> P2.4
 * D5 -> P2.5
 * D6 -> P2.6
 * D7 -> P2.7
 *
 * No Arduino APIs, HAL or RTOS.
 */

#include <reg51.h>
#include <intrins.h>

/* LCD control pins */
sbit LCD_RS = P2^0;
sbit LCD_RW = P2^1;
sbit LCD_EN = P2^2;

/* LCD data pins */
sbit LCD_D4 = P2^4;
sbit LCD_D5 = P2^5;
sbit LCD_D6 = P2^6;
sbit LCD_D7 = P2^7;

/* Function declarations */
void delay_ms(unsigned int ms);
void lcd_enable_pulse(void);
void lcd_send_nibble(unsigned char nibble);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char dat);
void lcd_init(void);
void lcd_string(char *str);

/* ---------------------------------------
   Timer0-based delay
   Approximately 1 ms per timer overflow
   at 11.0592 MHz (classic 12T 8051)
   --------------------------------------- */

void delay_ms(unsigned int ms)
{
    unsigned int i;

    for(i = 0; i < ms; i++)
    {
        TH0 = 0xFC;
        TL0 = 0x66;

        TF0 = 0;
        TR0 = 1;

        while(TF0 == 0);

        TR0 = 0;
    }
}

/* ---------------------------------------
   LCD Enable pulse
   --------------------------------------- */

void lcd_enable_pulse(void)
{
    LCD_EN = 1;

    _nop_();
    _nop_();
    _nop_();
    _nop_();

    LCD_EN = 0;

    _nop_();
    _nop_();
    _nop_();
    _nop_();
}

/* ---------------------------------------
   Send 4-bit data to LCD
   --------------------------------------- */

void lcd_send_nibble(unsigned char nibble)
{
    LCD_D4 = (nibble & 0x01) ? 1 : 0;
    LCD_D5 = (nibble & 0x02) ? 1 : 0;
    LCD_D6 = (nibble & 0x04) ? 1 : 0;
    LCD_D7 = (nibble & 0x08) ? 1 : 0;

    lcd_enable_pulse();
}

/* ---------------------------------------
   Send command to LCD
   --------------------------------------- */

void lcd_cmd(unsigned char cmd)
{
    LCD_RS = 0;
    LCD_RW = 0;

    /* Send upper 4 bits */
    lcd_send_nibble(cmd >> 4);

    /* Send lower 4 bits */
    lcd_send_nibble(cmd & 0x0F);

    /* Allow LCD to execute command */
    delay_ms(2);
}

/* ---------------------------------------
   Send character to LCD
   --------------------------------------- */

void lcd_data(unsigned char dat)
{
    LCD_RS = 1;
    LCD_RW = 0;

    /* Send upper 4 bits */
    lcd_send_nibble(dat >> 4);

    /* Send lower 4 bits */
    lcd_send_nibble(dat & 0x0F);

    delay_ms(2);
}

/* ---------------------------------------
   LCD Initialization - 4-bit mode
   --------------------------------------- */

void lcd_init(void)
{
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;

    delay_ms(20);

    /* HD44780 4-bit initialization sequence */
    lcd_send_nibble(0x03);
    delay_ms(5);

    lcd_send_nibble(0x03);
    delay_ms(1);

    lcd_send_nibble(0x03);
    delay_ms(1);

    lcd_send_nibble(0x02);
    delay_ms(1);

    /* Function Set: 4-bit, 2 lines, 5x8 font */
    lcd_cmd(0x28);

    /* Display ON, Cursor OFF, Blink OFF */
    lcd_cmd(0x0C);

    /* Entry Mode: Increment cursor, no display shift */
    lcd_cmd(0x06);

    /* Clear Display */
    lcd_cmd(0x01);
}

/* ---------------------------------------
   Display a string
   --------------------------------------- */

void lcd_string(char *str)
{
    while(*str != '\0')
    {
        lcd_data(*str);
        str++;
    }
}

/* ---------------------------------------
   Main Program - Task 7A
   --------------------------------------- */

void main(void)
{
    /* Timer0 Mode 1 - 16-bit timer */
    TMOD = (TMOD & 0xF0) | 0x01;

    TR0 = 0;
    TF0 = 0;

    lcd_init();

    /* First row */
    lcd_cmd(0x80);
    lcd_data('A');
    lcd_string("T89S52 LCD");

    /* Second row */
    lcd_cmd(0xC0);
    lcd_string("Hello 8051");

    while(1)
    {
        /* LCD continuously displays the text */
    }
}
