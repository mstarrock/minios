ENTRY(_start)

#include "sys_config.h"

STACK_SIZE = 4K;

SECTIONS
{
    . = 0x00000000;
    .text : { *(.text) }
    .rodata : { *(.rodata) }

    _data_from_start = .;
    _data_from_end = _data_from_start + SIZEOF(.data);
    . = SYS_MEM_ADDR+SYS_MEM_SIZE-SIZEOF(.data)-SIZEOF(.bss);
    _data_to_start = .;
    .data : AT(LOADADDR(.rodata)+SIZEOF(.rodata)) { *(.data) . = ALIGN(4);}

    _bss_start = .;
    _bss_end = _bss_start + SIZEOF(.bss);
    .bss : { *(.bss) . = ALIGN(4);}

    _stack_start = . + STACK_SIZE;
}

