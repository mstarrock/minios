#include "config.h"
#include "types.h"
#include "cpu.h"
#include "exception.h"
#include "interrupt.h"
#include "timer.h"
#include "scheduler.h"

#define GET_CPU_PRI_MEM_REG(x) do { \
        asm("mrc p15, 4, %0, c15, c0, 0\n\t" \
            : "=r" (cpu_priv_mem)); \
    }while(0)

uint8_t *cpu_priv_mem;

struct pc_uart_reg
{
    uint32_t DR;
    uint32_t SR;
    uint32_t resv_0[4];
    const uint32_t FR;
    uint32_t resv_1;
    uint32_t ILPR;
    uint32_t IBRD;
    uint32_t FBRD;
    uint32_t LCR_H;
    uint32_t CR;
    uint32_t IFLS;
    uint32_t IMSC;
    const uint32_t RIS;
    const uint32_t MIS;
    uint32_t ICR;
    uint32_t DMACR;
    uint32_t resv_2[13];
    uint32_t resv_3[4];
    uint32_t resv_4[976];
    uint32_t resv_5[4];
    const uint32_t PERIPHID0;
    const uint32_t PERIPHID1;
    const uint32_t PERIPHID2;
    const uint32_t PERIPHID3;
    const uint32_t CELLID0;
    const uint32_t CELLID1;
    const uint32_t CELLID2;
    const uint32_t CELLID3;
}__attribute__((packed));

static volatile struct pc_uart_reg * const uart0 = (volatile struct pc_uart_reg *)0x10009000;

void puts(char *s)
{
    while(*s)
    {
        while(uart0->FR & 0x08) ;
        uart0->DR = *s;
        s++;
    }
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

/*
 * this function is used for testing invalid instruction
 * exception handle
 */
static void _call_invl_inst(void)
{
    puts("before invalid instruction.\n");
    asm("mrc p15, 0, r0, c12, c0, 4");
    puts("after invalid instruction.\n");
}

void kernel_start(void)
{
    puts("Hello World From Kernel!\n");

    /* install exception vector */
    excpt_init(NULL);

    //_call_invl_inst();

    GET_CPU_PRI_MEM_REG(cpu_priv_mem);

    /* init interrupt */
    intr_init();

    /* init timer */
    timer_init(cpu_priv_mem);

    /* init and start scheduler - here should never return */
    scheduler_init();
    scheduler_start();

    puts("kernel halt.");
    while(1) ;
}

