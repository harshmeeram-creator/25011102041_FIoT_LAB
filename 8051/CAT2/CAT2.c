
#include <reg51.h>

sbit LED = P1^0;

// Custom delay library function
void delay_ms(unsigned int ms)
{
    unsigned int i, j;

    for(i = 0; i < ms; i++)
    {
        for(j = 0; j < 123; j++);
    }
}

void main()
{
    LED = 0;

    while(1)
    {
        LED = 1;
        delay_ms(500);

        LED = 0;
        delay_ms(500);
    }
}
