ENTRY(_start)

KERNEL_HEADER_SIZE = 64;
KERNEL_STACK_SIZE = 4K;
KERNEL_EXCEPT_STACK_SIZE = 4K;

MEMORY
{
    header : ORIGIN = 0x00000000, LENGTH = KERNEL_HEADER_SIZE
    ddr    : ORIGIN = 0x60000000, LENGTH = 64M
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
}

