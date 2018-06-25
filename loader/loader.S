.arm
.global _start

.text
_start:
    ldr r2, _uart_reg_cr
    ldr r3, _uart_cr_init
    str r3, [r2]

    ldr r2, _uart_reg_dr
    ldr r3, =_hw_str
    mov r4, #1
_print:
    ldrb r5, [r3]
    cmp r5, #0
    beq _end
    str r5, [r2]
    add r3, r4, r3
    bl _print
_end:
    bl _end
    nop

_uart_reg_dr:
    .word 0x10009000
_uart_reg_cr:
    .word 0x10009030
_uart_cr_init:
    .word 0x00000101

.data
_hw_str:
    .byte 0x48,0x65,0x6c,0x6c,0x6f,0x20,0x57,0x6f,0x72,0x6c,0x64,0x21,0x0a,0x00
