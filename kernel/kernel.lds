ENTRY(_start)

#include "sys_config.h"

KERNEL_HEADER_SIZE = 64;
KERNEL_STACK_SIZE = 8K;
KERNEL_EXCEPT_STACK_SIZE = 4K;

MEMORY
{
    header : ORIGIN = 0x00000000, LENGTH = KERNEL_HEADER_SIZE
    ddr    : ORIGIN = SYS_MEM_ADDR, LENGTH = SYS_MEM_SIZE
}

SECTIONS
{
    .header : AT(0x0)
    {
        LONG(LOADADDR(.text)-LOADADDR(.header));
        LONG(SIZEOF(.text)+SIZEOF(.rodata)+SIZEOF(.data));
        LONG(ADDR(.text));
        FILL(0x00000000);
        . = ORIGIN(header)+LENGTH(header);
    } > header

    .text : AT(LOADADDR(.header)+SIZEOF(.header))
    {
        *(.text)
    } > ddr

    .rodata :
    {
        *(.rodata)
    } > ddr

    .data :
    {
        *(.data)
        . = ALIGN(4);
    } > ddr

    _bss_start = .;
    _bss_end = _bss_start + SIZEOF(.bss);
    .bss :
    {
        *(.bss)
        . = ALIGN(4);
    } > ddr

    . = . + KERNEL_STACK_SIZE;
    _kernel_stack_start = .;

    . = . + KERNEL_EXCEPT_STACK_SIZE;
    _kernel_except_stack_start = .;

    _mem_pool_start = ALIGN(4096);
    _mem_pool_end = ORIGIN(ddr)+LENGTH(ddr)-1;
}

