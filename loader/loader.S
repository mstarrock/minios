.arm
.global _start
.extern loader_start_c

.text
_start:
    /* setup stack */
    ldr r13, =_stack_start

    /* copy data section into DDR */
    ldr r0, =_data_from_start
    ldr r1, =_data_from_end
    ldr r2, =_data_to_start
_copy_data_section:
    cmp r0, r1
    bge _copy_data_section_done
    ldr r3, [r0]
    str r3, [r2]
    add r0, r0, #4
    add r2, r2, #4
    b _copy_data_section
_copy_data_section_done:

    /* clear bss section */
    ldr r0, =_bss_start
    ldr r1, =_bss_end
    bfc r2, #0, #32
_clear_bss_section:
    cmp r0, r1
    bge _clear_bss_section_done
    str r2, [r0]
    add r0, r0, #4
    b _clear_bss_section
_clear_bss_section_done:

    /* print loader message */
    ldr r2, _uart_reg_cr
    ldr r3, _uart_cr_init
    str r3, [r2]

    ldr r2, _uart_reg_dr
    ldr r3, =_hw_str
    mov r4, #1
_print:
    ldrb r5, [r3]
    cmp r5, #0
    beq _print_end
    str r5, [r2]
    add r3, r4, r3
    b _print
_print_end:
    /* jump into c code environment, this should never return */
    b loader_start_c
_end:
    b _end
    nop

_uart_reg_dr:
    .word 0x10009000
_uart_reg_cr:
    .word 0x10009030
_uart_cr_init:
    .word 0x00000101

.section .rodata
_hw_str:
    .byte 'b','o','o','t','l','o','a','d','e','r',' '
    .byte 'r','u','n','n','i','n','g',0x0a,0x00
