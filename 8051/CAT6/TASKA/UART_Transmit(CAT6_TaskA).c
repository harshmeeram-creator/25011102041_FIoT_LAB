/*
 * Task A - UART Initialization and Character Transmission
 * AT89S52 @ 11.0592 MHz, UART Mode 1, 9600-8-N-1
 *
 * Continuously transmits "Hello from 8051" to a PC terminal (PuTTY)
 * over a USB-to-TTL converter.
 */

#include <REGX52.H>

void uart_init(void);
void uart_putchar(unsigned char c);
void uart_putstring(char *s);
void delay_ms(unsigned int ms);

void main(void)
{
    uart_init();

    while (1)
    {
        uart_putstring("Hello from 8051\r\n");
        delay_ms(500);
    }
}

/* Configure UART: Mode 1 (8-bit, variable baud), Timer 1 Mode 2
 * (auto-reload) generating 9600 baud at 11.0592 MHz. */
void uart_init(void)
{
    TMOD &= 0x0F;   /* clear Timer1 bits, keep Timer0 bits untouched */
    TMOD |= 0x20;   /* Timer1 -> Mode 2 (8-bit auto-reload)          */
    TH1 = 0xFD;      /* reload value for 9600 baud @ 11.0592 MHz     */
    TL1 = 0xFD;      /* initial counter value                        */
    TR1 = 1;         /* start Timer1                                 */
    SCON = 0x50;     /* Mode 1, REN=1 (reception enabled)            */
    TI = 0;
    RI = 0;
}

/* Send one byte and wait until the hardware finishes shifting it out. */
void uart_putchar(unsigned char c)
{
    SBUF = c;
    while (TI == 0);
    TI = 0;
}

/* Send a null-terminated string, one character at a time. */
void uart_putstring(char *s)
{
    while (*s)
    {
        uart_putchar(*s);
        s++;
    }
}

/* Rough busy-wait delay. Not cycle-accurate - recalibrate the inner
 * loop count on your actual board/crystal if timing needs to be precise. */
void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 120; j++);
}