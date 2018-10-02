.arm
.global _start
.extern kernel_start

#define USE_SUPV_STACK (1)

.section .text
_start:
    /* setup exception vector base */
    ldr r0, =_excp_vector
    mcr p15, 0, r0, c12, c0, 0
    mrc p15, 0, r1, c12, c0, 0

    /* setup stack */
    ldr sp, =_kernel_stack_start

#if(USE_SUPV_STACK == 0)
    /* setup stack to other processor mode */
    mrs r0, cpsr

    cps #27
    ldr sp, =_kernel_except_stack_start

    msr cpsr, r0
#endif

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

/* exception handler structure */
.align 5
.global _excp_vector
_excp_vector:
    ldr pc, _excp_addr_rst
    ldr pc, _excp_addr_invd_inst
    ldr pc, _excp_addr_svc
    ldr pc, _excp_addr_pref_abort
    ldr pc, _excp_addr_data_abort
    ldr pc, _excp_addr_hyp_trap
    ldr pc, _excp_addr_irq
    ldr pc, _excp_addr_fiq

_deadloop:
    b .

.extern eh_invd_inst

_except_invd_inst:
#if(USE_SUPV_STACK == 1)
    srsdb sp!, #19
    cps #19
    stmdb sp!, {r0-r12}
#else
    srsdb sp!, #27
#endif
    bl eh_invd_inst
    ldmia sp!, {r0-r12}
    rfeia sp!
    subs pc, lr, #0

_excp_addr:
_excp_addr_rst:        .word _deadloop
_excp_addr_invd_inst:  .word _except_invd_inst
_excp_addr_svc:        .word _deadloop
_excp_addr_pref_abort: .word _deadloop
_excp_addr_data_abort: .word _deadloop
_excp_addr_hyp_trap:   .word _deadloop
_excp_addr_irq:        .word _deadloop
_excp_addr_fiq:        .word _deadloop

