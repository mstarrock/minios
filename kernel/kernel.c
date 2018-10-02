#include "types.h"

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

static char str[] = {"Hello World From Kernel!\n"};

void puts(char *s)
{
    while(*s)
    {
        while(uart0->FR & 0x08) ;
        uart0->DR = *s;
        s++;
    }
}

void eh_invd_inst(void)
{
    puts("invalid instruction.\n");
}

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
    puts(str);

    //_call_invl_inst();

    puts("kernel halt.");
    while(1) ;
}

