/* ============================================================
   FPIoT Lab CAT3 - Timer-Based LED Pattern Generator
   and Button Interrupt (Polled) Controller
   Board    : AT89S52 (8051 family)
   Compiler : Keil C51 - bare-metal, register-level only
              (no Arduino APIs, no HAL, no RTOS)

   Hardware:
     LED1 -> P1.0   LED2 -> P1.1   LED3 -> P1.2   LED4 -> P1.3
     Assumes active-HIGH LEDs: pin = 1 turns the LED ON, matching
     your schematic (P1.x -> resistor -> LED -> common GND rail).
     If your LEDs light when the pin is LOW instead, invert every
     value written to P1 in the mode functions below.

     Push-button: wired between P2.3 and P2.7, no external pull
     resistor needed.
       - P2.3 is held permanently LOW by firmware ("virtual ground")
       - P2.7 is read as input:
           button open    -> P2.7 pulled HIGH by internal pull-up -> reads 1
           button pressed -> P2.7 shorted to P2.3's LOW           -> reads 0

   Timing assumes a 12 MHz crystal (1 machine cycle = 1 us).
   If your board uses 11.0592 MHz, the delay will drift slightly
   but LED speeds will still look fine.
   ============================================================ */

#include <reg51.h>

sbit LED1 = P1^0;

sbit LED2 = P1^1;
sbit LED3 = P1^2;
sbit LED4 = P1^3;

sbit SW_REF = P2^3;   /* driven permanently LOW  - "virtual ground" */
sbit SW_IN  = P2^7;   /* input - reads 0 only when button is pressed */

#define DEBOUNCE_MS    20     /* per your notes: 20 ms debounce         */
#define STEP_DELAY_MS  500    /* speed of each pattern step - tweak me  */

/* ---------------- Timer0-based 1 ms delay (12 MHz) ---------------- */
void delay_ms(unsigned int ms)
{
    unsigned int i;
    TMOD = (TMOD & 0xF0) | 0x01;   /* Timer0 = Mode 1, 16-bit timer */
    for (i = 0; i < ms; i++)
    {
        TH0 = 0xFC;                 /* reload for ~1 ms @ 12 MHz   */
        TL0 = 0x18;
        TR0 = 1;                    /* start timer0                */
        while (TF0 == 0);           /* wait for overflow           */
        TR0 = 0;                    /* stop timer0                 */
        TF0 = 0;                    /* clear overflow flag         */
    }
}

/* ---------------------------- I/O setup ---------------------------- */
void io_init(void)
{
    P1 = 0x00;      /* all LEDs OFF at power-up */
    SW_REF = 0;     /* P2.3 permanently low - "virtual ground" for switch */
    SW_IN  = 1;     /* P2.7 as input - lets internal pull-up hold it high */
}

/* --------------------------------------------------------------------
   Returns 1 once, for a single validated press+release cycle.
   Blocks only while the button is actually held down, so pattern loops
   stay responsive the rest of the time. Guarantees exactly one mode
   transition per physical press.
   -------------------------------------------------------------------- */
bit button_pressed(void)
{
    if (SW_IN == 0)
    {
        delay_ms(DEBOUNCE_MS);        /* debounce the press      */
        if (SW_IN == 0)               /* still low -> real press */
        {
            while (SW_IN == 0);       /* wait for release        */
            delay_ms(DEBOUNCE_MS);    /* debounce the release    */
            return 1;
        }
    }
    return 0;
}

/* ------------------------- Mode 1: Running LED ------------------------- */
void mode1_running(void)
{
    unsigned char pattern[4] = {0x01, 0x02, 0x04, 0x08};
    unsigned char pos = 0;

    P1 = pattern[pos];
    while (1)
    {
        delay_ms(STEP_DELAY_MS);
        if (button_pressed()) return;      /* advance to Mode 2 */
        pos = (pos + 1) % 4;
        P1 = pattern[pos];
    }
}

/* ------------------------ Mode 2: Binary Counter ------------------------ */
void mode2_binary_counter(void)
{
    unsigned char count = 0;

    P1 = count;
    while (1)
    {
        delay_ms(STEP_DELAY_MS);
        if (button_pressed()) return;      /* advance to Mode 3 */
        count = (count + 1) & 0x0F;        /* wraps 0000..1111  */
        P1 = count;
    }
}

/* ----------------------- Mode 3: Alternating Pattern --------------------- */
void mode3_alternating(void)
{
    bit toggle = 0;

    P1 = 0x0A;      /* 1010 */
    while (1)
    {
        delay_ms(STEP_DELAY_MS);
        if (button_pressed()) return;      /* advance to Mode 4 */
        toggle = !toggle;
        P1 = toggle ? 0x05 : 0x0A;         /* 0101 <-> 1010 */
    }
}

/* -------------------------- Mode 4: All LED Flash ------------------------ */
void mode4_flash_all(void)
{
    bit toggle = 0;

    P1 = 0x0F;      /* 1111 */
    while (1)
    {
        delay_ms(STEP_DELAY_MS);
        if (button_pressed()) return;      /* advance back to Mode 1 */
        toggle = !toggle;
        P1 = toggle ? 0x00 : 0x0F;         /* 0000 <-> 1111 */
    }
}

/* --------------------------------- main --------------------------------- */
void main(void)
{
    unsigned char mode = 0;   /* 0=Mode1 .. 3=Mode4 */

    io_init();
    P1 = 0x00;                        /* idle: all LEDs off */
    while (button_pressed() == 0);    /* wait for first press to start Mode1 */

    while (1)
    {
        switch (mode)
        {
            case 0: mode1_running();        break;
            case 1: mode2_binary_counter();  break;
            case 2: mode3_alternating();     break;
            case 3: mode4_flash_all();       break;
        }
        mode = (mode + 1) % 4;   /* cycle back to Mode1 after Mode4 */
    }
}