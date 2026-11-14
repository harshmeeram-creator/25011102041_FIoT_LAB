
/*
 * CAT5 - Task 2: LED Fading using Software PWM
 *
 * Controller : AT89S52
 * Compiler   : Keil C51
 * Crystal    : 11.0592 MHz
 * Timer      : Timer0, Mode 1 (16-bit)
 * LED        : P1.0 (Active HIGH)
 *
 * Timer interrupt : Approximately 100.26 us
 * PWM frequency   : Approximately 997 Hz
 *
 * Duty cycle:
 * 0%, 10%, 20%, ... 100%, ... 10%, 0%
 *
 * No software delay loops.
 */

#include <reg51.h>

sbit LED = P1^0;

#define TIMER0_HIGH  0xFF
#define TIMER0_LOW   0xA4

#define PWM_STEPS    10U
#define FADE_DELAY   100U

volatile unsigned char pwm_count = 0;
volatile unsigned char brightness = 0;
volatile unsigned char fade_count = 0;
volatile unsigned char fade_up = 1;

void Timer0_ISR(void) interrupt 1
{
    TH0 = TIMER0_HIGH;
    TL0 = TIMER0_LOW;

    /* Software PWM generation */
    if (pwm_count < brightness)
        LED = 1;
    else
        LED = 0;

    pwm_count++;

    if (pwm_count >= PWM_STEPS)
    {
        pwm_count = 0;

        fade_count++;

        if (fade_count >= FADE_DELAY)
        {
            fade_count = 0;

            if (fade_up == 1)
            {
                if (brightness < PWM_STEPS)
                    brightness++;

                if (brightness >= PWM_STEPS)
                    fade_up = 0;
            }
            else
            {
                if (brightness > 0)
                    brightness--;
                else
                    fade_up = 1;
            }
        }
    }
}

void Timer0_Init(void)
{
    TMOD &= 0xF0;
    TMOD |= 0x01;

    TH0 = TIMER0_HIGH;
    TL0 = TIMER0_LOW;

    TF0 = 0;
    ET0 = 1;
    EA = 1;
    TR0 = 1;
}

void main(void)
{
    LED = 0;

    pwm_count = 0;
    brightness = 0;
    fade_count = 0;
    fade_up = 1;

    Timer0_Init();

    while (1)
    {
        /* PWM and fading handled by Timer0 interrupt */
    }
}
