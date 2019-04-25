#include "types.h"
#include "uart.h"

#include "misc.h"

void puts(char *s)
{
    uart_puts(s);
}

#if 0
char *itoa(char *str, int32_t val)
{
    char *ptr = str;;
    int32_t base = 1000000000;
    int8_t digit;

    if(val < 0)
    {
        val = -val;
        *ptr++ = '-';
    }

    /* leading zero */
    while(base)
    {
        digit = val/base;
        if(digit != 0)
            break;

        val -= (digit*base);
        base /= 10;
    }

    /* main number */
    while(digit)
    {
        *ptr++ = digit+'0';
        val -= (digit*base);
        base /= 10;
        if(base == 0)
            break;

        digit = val/base;
    }

    *ptr = '\0';
    return str;
}
#endif

void *memcpy (void * destination, const void *source, size_t num)
{
    while(num>=0)
    {
        ((char *)destination)[num-1] = ((char *)source)[num-1];
        num--;
    }
}

char *strncpy(char *destination, const char *source, size_t num)
{
    while(num)
    {
        if(*source)
            *destination = *source;
        else
            *destination = 0;

        destination++;
        source++;
        num--;
    }
}

