
#include <REG51.H>
#include <intrins.h>

/* LCD pin connections */
sbit LCD_RS = P2^0;
sbit LCD_RW = P2^1;
sbit LCD_EN = P2^2;

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
void lcd_goto(unsigned char row, unsigned char column);
void lcd_puts(char *str);
void lcd_print_number(unsigned int value);

/* Timer0 delay - approximately 1 ms per iteration */
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

/* LCD Enable pulse */
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

/* Send 4-bit data */
void lcd_send_nibble(unsigned char nibble)
{
    LCD_D4 = (nibble & 0x01) ? 1 : 0;
    LCD_D5 = (nibble & 0x02) ? 1 : 0;
    LCD_D6 = (nibble & 0x04) ? 1 : 0;
    LCD_D7 = (nibble & 0x08) ? 1 : 0;

    lcd_enable_pulse();
}

/* Send LCD command */
void lcd_cmd(unsigned char cmd)
{
    LCD_RS = 0;
    LCD_RW = 0;

    lcd_send_nibble(cmd >> 4);
    lcd_send_nibble(cmd & 0x0F);

    delay_ms(2);
}

/* Send LCD character */
void lcd_data(unsigned char dat)
{
    LCD_RS = 1;
    LCD_RW = 0;

    lcd_send_nibble(dat >> 4);
    lcd_send_nibble(dat & 0x0F);

    delay_ms(2);
}

/* LCD initialization */
void lcd_init(void)
{
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;

    delay_ms(20);

    lcd_send_nibble(0x03);
    delay_ms(5);

    lcd_send_nibble(0x03);
    delay_ms(1);

    lcd_send_nibble(0x03);
    delay_ms(1);

    lcd_send_nibble(0x02);
    delay_ms(1);

    lcd_cmd(0x28);  /* 4-bit, 2-line mode */
    lcd_cmd(0x0C);  /* Display ON, cursor OFF */
    lcd_cmd(0x06);  /* Auto increment cursor */
    lcd_cmd(0x01);  /* Clear display */
}

/* Move cursor to specified row and column
   Row: 1 or 2
   Column: 1 to 16 */
void lcd_goto(unsigned char row, unsigned char column)
{
    unsigned char address;

    if(row == 1 && column >= 1 && column <= 16)
    {
        address = 0x80 + column - 1;
    }
    else if(row == 2 && column >= 1 && column <= 16)
    {
        address = 0xC0 + column - 1;
    }
    else
    {
        return;
    }

    lcd_cmd(address);
}

/* Display a string */
void lcd_puts(char *str)
{
    while(*str != '\0')
    {
        lcd_data(*str);
        str++;
    }
}

/* Display an unsigned integer */
void lcd_print_number(unsigned int value)
{
    char digits[5];
    unsigned char i = 0;

    if(value == 0)
    {
        lcd_data('0');
        return;
    }

    while(value > 0)
    {
        digits[i] = (value % 10) + '0';
        value = value / 10;
        i++;
    }

    while(i > 0)
    {
        i--;
        lcd_data(digits[i]);
    }
}

/* Main program */
void main(void)
{
    TMOD = (TMOD & 0xF0) | 0x01;

    TR0 = 0;
    TF0 = 0;

    lcd_init();

    lcd_goto(1, 1);
    lcd_puts("Value: ");
    lcd_print_number(12345);

    lcd_goto(2, 1);
    lcd_puts("LCD Task 7B");

    while(1)
    {
    }
}
