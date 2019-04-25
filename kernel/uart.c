#include "types.h"

#include "uart.h"

static volatile struct pc_uart_reg * const uart0 = (volatile struct pc_uart_reg *)0x10009000;

void uart_init(void)
{

}

void uart_puts(char *s)
{
    while(*s)
    {
        while(uart0->FR & 0x08) ;
        uart0->DR = *s;
        s++;
    }
}

