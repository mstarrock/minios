#include "config.h"
#include "types.h"
#include "cpu.h"
#include "exception.h"
#include "interrupt.h"
#include "timer.h"
#include "scheduler.h"
#include "uart.h"
#include "misc.h"

#define GET_CPU_PRI_MEM_REG(x) do { \
        asm("mrc p15, 4, %0, c15, c0, 0\n\t" \
            : "=r" (cpu_priv_mem)); \
    }while(0)

uint8_t *cpu_priv_mem;

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
    uart_init();

    puts("Hello World From Kernel!\n");

    /* install exception vector */
    excpt_init(NULL);

#if 0
    _call_invl_inst();
    while(1) ;
#endif

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

