
#include <REG51.H>
#include <intrins.h>

/* LCD CONNECTIONS */
sbit LCD_RS = P2^0;
sbit LCD_RW = P2^1;
sbit LCD_EN = P2^2;

sbit LCD_D4 = P2^4;
sbit LCD_D5 = P2^5;
sbit LCD_D6 = P2^6;
sbit LCD_D7 = P2^7;

/* KEYPAD ROWS */
sbit R1 = P1^0;
sbit R2 = P1^1;
sbit R3 = P1^2;
sbit R4 = P1^3;

/* KEYPAD COLUMNS */
sbit C1 = P1^4;
sbit C2 = P1^5;
sbit C3 = P1^6;
sbit C4 = P1^7;

/* CHARACTER POSITION */
unsigned char row = 1;
unsigned char col = 1;

/* FUNCTION DECLARATIONS */
void delay_ms(unsigned int ms);
void lcd_enable_pulse(void);
void lcd_send_nibble(unsigned char nibble);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char dat);
void lcd_init(void);
void lcd_goto(unsigned char r, unsigned char c);
void lcd_puts(char *str);
unsigned char keypad_getkey(void);
void keypad_scan(void);
void display_character(void);
void move_character(unsigned char key);

/* TIMER0 DELAY */
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

/* LCD ENABLE */
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

/* SEND LCD NIBBLE */
void lcd_send_nibble(unsigned char nibble)
{
    LCD_D4 = (nibble & 0x01) ? 1 : 0;
    LCD_D5 = (nibble & 0x02) ? 1 : 0;
    LCD_D6 = (nibble & 0x04) ? 1 : 0;
    LCD_D7 = (nibble & 0x08) ? 1 : 0;

    lcd_enable_pulse();
}

/* LCD COMMAND */
void lcd_cmd(unsigned char cmd)
{
    LCD_RS = 0;
    LCD_RW = 0;

    lcd_send_nibble(cmd >> 4);
    lcd_send_nibble(cmd & 0x0F);

    delay_ms(2);
}

/* LCD DATA */
void lcd_data(unsigned char dat)
{
    LCD_RS = 1;
    LCD_RW = 0;

    lcd_send_nibble(dat >> 4);
    lcd_send_nibble(dat & 0x0F);

    delay_ms(2);
}

/* LCD INITIALIZATION */
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

    lcd_cmd(0x28);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
}

/* LCD CURSOR POSITION */
void lcd_goto(unsigned char r, unsigned char c)
{
    if(r == 1 && c >= 1 && c <= 16)
        lcd_cmd(0x80 + c - 1);

    else if(r == 2 && c >= 1 && c <= 16)
        lcd_cmd(0xC0 + c - 1);
}

/* DISPLAY STRING */
void lcd_puts(char *str)
{
    while(*str != '\0')
    {
        lcd_data(*str);
        str++;
    }
}

/* KEYPAD SCANNING */
unsigned char keypad_getkey(void)
{
    unsigned char key = 0;
    unsigned char r;

    P1 = 0xFF;

    /* ROW 1 */
    R1 = 0;
    if(C1 == 0) key = '1';
    else if(C2 == 0) key = '2';
    else if(C3 == 0) key = '3';
    else if(C4 == 0) key = 'A';
    R1 = 1;

    /* ROW 2 */
    if(key == 0)
    {
        R2 = 0;
        if(C1 == 0) key = '4';
        else if(C2 == 0) key = '5';
        else if(C3 == 0) key = '6';
        else if(C4 == 0) key = 'B';
        R2 = 1;
    }

    /* ROW 3 */
    if(key == 0)
    {
        R3 = 0;
        if(C1 == 0) key = '7';
        else if(C2 == 0) key = '8';
        else if(C3 == 0) key = '9';
        else if(C4 == 0) key = 'C';
        R3 = 1;
    }

    /* ROW 4 */
    if(key == 0)
    {
        R4 = 0;
        if(C1 == 0) key = '*';
        else if(C2 == 0) key = '0';
        else if(C3 == 0) key = '#';
        else if(C4 == 0) key = 'D';
        R4 = 1;
    }

    P1 = 0xFF;

    return key;
}

/* DISPLAY MOVABLE CHARACTER */
void display_character(void)
{
    lcd_cmd(0x01);

    lcd_goto(row, col);
    lcd_data('*');
}

/* CHARACTER MOVEMENT */
void move_character(unsigned char key)
{
    if(key == '1')
    {
        if(row > 1)
            row--;
    }
    else if(key == '2')
    {
        if(row < 2)
            row++;
    }
    else if(key == '+')
    {
        if(col > 1)
            col--;
    }
    else if(key == '-')
    {
        if(col < 16)
            col++;
    }

    display_character();
}

/* MAIN PROGRAM */
void main(void)
{
    unsigned char key;

    TMOD = (TMOD & 0xF0) | 0x01;
    TR0 = 0;
    TF0 = 0;

    P1 = 0xFF;

    lcd_init();

    lcd_cmd(0x80);
    lcd_puts("KEYPAD CONTROL");

    delay_ms(1000);

    display_character();

    while(1)
    {
        key = keypad_getkey();

        if(key != 0)
        {
            delay_ms(30);

            if(keypad_getkey() == key)
            {
                if(key == '1' || key == '2')
                    move_character(key);

                else if(key == 'Q')
                {
                    lcd_cmd(0x01);
                    lcd_goto(1,1);
                    lcd_puts("SEARCH");
                    delay_ms(1000);
                    display_character();
                }

                else if(key == 'H')
                {
                    lcd_cmd(0x01);
                    lcd_goto(1,1);
                    lcd_puts("1:UP 2:DOWN");
                    lcd_goto(2,1);
                    lcd_puts("+:LEFT -:RIGHT");
                    delay_ms(2000);
                    display_character();
                }

                while(keypad_getkey() != 0);
                delay_ms(30);
            }
        }
    }
}
