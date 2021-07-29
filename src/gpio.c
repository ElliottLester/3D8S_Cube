#include <gpio.h>

bool setPort(unsigned short m, BYTE value)
{
    switch(m)
    {
        case MODE_DATA:
            P0 = ~value;
            break;
        case MODE_PLANE:
            P1 = ~value;
            break;
        case MODE_LATCH:
            P2 = value;
            break;
        default:
            return false;
    }
    return true;
}

void delay(unsigned long milliseconds)
{
    const unsigned long ClocksPerMillisecond = FOSC / 12 / 2500; // magic numbers
    for (unsigned long i = milliseconds; i > 0; --i)
    {
        for (unsigned long clks = ClocksPerMillisecond; clks > 0; --clks )
        {
            __asm // 10 noops
            nop;
            nop;
            nop;
            nop;
            nop;
            nop;
            nop;
            nop;
            nop;
            nop;
            nop;
            __endasm;
        }
    }
}
