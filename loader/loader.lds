ENTRY(_start)

#include "sys_config.h"

DATA_SIZE = 4K;
STACK_SIZE = 4K;

MEMORY
{
    rom : ORIGIN = 0x00000000, LENGTH = 64M
    data : ORIGIN = (SYS_MEM_ADDR + SYS_MEM_SIZE - DATA_SIZE - STACK_SIZE), LENGTH = DATA_SIZE
}

SECTIONS
{
    . = 0x00000000;
    .text : { *(.text) } > rom
    .rodata : { *(.rodata) } > rom

    _data_from_start = .;
    _data_from_end = _data_from_start + SIZEOF(.data);

    .data : AT(LOADADDR(.rodata)+SIZEOF(.rodata)) { _data_to_start = .; *(.data) . = ALIGN(4);} > data

    _bss_start = .;
    _bss_end = _bss_start + SIZEOF(.bss);
    .bss : { *(.bss) . = ALIGN(4);} > data

    _stack_start = . + STACK_SIZE;
}

