#include "config.h"
#include "cpu.h"
#include "types.h"

#include "exception.h"

static excpt_handle handler[ET_ALL];

#if EXCPT_VECTOR_IN_C
#define EXCPT_ENTRY __attribute__((naked)) static

#if USE_SUPV_STACK
#define EXCPT_START(x) do { \
        asm volatile("sub lr, lr, #"#x"\n\t" \
            "srsdb sp!, #19\n\t" \
            "cps #19\n\t" \
            "stmdb sp!, {r0-r12}\n\t"); \
        }while(0)
#else
#define EXCPT_START(x) do { \
        asm volatile("sub lr, lr, #"#x"\n\t" \
        "srsdb sp!, #27\n\t" \
        "stmdb sp!, {r0-r12}\n\t"); \
        }while(0)
#endif

#define EXCPT_END() do {asm("ldmia sp!, {r0-r12}\n\t" \
        "rfeia sp!\n\t"); \
        }while(0)
#else
#define EXCPT_ENTRY
#define EXCPT_START(x)
#define EXCPT_END()
#endif

EXCPT_ENTRY void eh_dummy(void)
{
    while(1) ;
}

EXCPT_ENTRY void eh_invd_inst(void)
{
    EXCPT_START(0);

    //puts("invalid instruction.\n");
    if(handler[ET_UND])
        (handler[ET_UND])();

    EXCPT_END();
}

EXCPT_ENTRY void eh_irq(void)
{
    EXCPT_START(4);

    //puts("irq.\n");
    if(handler[ET_IRQ])
        (handler[ET_IRQ])();

    EXCPT_END();
}

EXCPT_ENTRY void eh_fiq(void)
{
    EXCPT_START(4);

    //puts("fiq.\n");
    if(handler[ET_FIQ])
        (handler[ET_FIQ])();

    EXCPT_END();
}

__attribute__((naked, aligned (64))) static void except_vector(void)
{
    asm("b eh_dummy\n\t"
        "b eh_invd_inst\n\t"
        "b eh_dummy\n\t"
        "b eh_dummy\n\t"
        "b eh_dummy\n\t"
        "b eh_dummy\n\t"
        "b eh_irq\n\t"
        "b eh_fiq\n\t");
}

void excpt_init(void *vector)
{
    if(NULL == vector)
        vector = (void *)except_vector;

#if EXCPT_VECTOR_IN_C
    /* setup exception vector base */
    asm("mcr p15, 0, %0, c12, c0, 0\n\t"
        :
        : "r" (vector));

    /*
     * If USE_SUPV_STACK config is enable, then the stack
     * is set by startup assembly code.
     */
#if !USE_SUPV_STACK
    /* setup stack to each processor mode */
    asm("mrs r0, cpsr\n\t"
        "cps %0\n\t"
        "ldr sp, =_kernel_except_stack_start\n\t"
        "cps %1\n\t"
        "ldr sp, =_kernel_except_stack_start\n\t"
        "cps %2\n\t"
        "ldr sp, =_kernel_except_stack_start\n\t"
        "cps %3\n\t"
        "ldr sp, =_kernel_except_stack_start\n\t"
        "cps %4\n\t"
        "ldr sp, =_kernel_except_stack_start\n\t"
        "msr cpsr, r0\n\t"
        :
        :"i" (CM_UND), "i" (CM_HYP), "i" (CM_ABT), "i" (CM_IRQ), "i" (CM_FIQ)
        :"r0");

#endif
#endif
}

void excpt_inst_handle(enum excpt_type type, excpt_handle func)
{
    if(ET_ALL > type)
        handler[type] = func;
}

