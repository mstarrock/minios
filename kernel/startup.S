.arm
.global _start
.extern kernel_start

.text
_start:
    /* setup stack */
    ldr r13, =_kernel_stack_start

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

    /* jump into c code environment, this should never return */
    b kernel_start
_end:
    b _end
    nop
