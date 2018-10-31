#include "config.h"
#include "types.h"
#include "cpu.h"
#include "exception.h"
#include "gic.h"

#include "interrupt.h"

#define CPU_ENABLE_IRQ(enable) do { \
        if(enable) \
            asm("cpsie i"); \
        else \
            asm("cpsid i"); \
    }while(0);

#define CPU_ENABLE_FIQ(enable) do { \
        if(enable) \
            asm("cpsie f"); \
        else \
            asm("cpsid f"); \
    }while(0);

static intr_handle handler[256];

static void irq_handler(void)
{
    /* invoke related interrupt handler */
    struct arm_gic_intr_id id;
    arm_gic_intr_ack(&id);

    if((id.int_id != INVLD_INTR_ID) && (NULL != handler[id.int_id]))
        handler[id.int_id](id.int_id);

    arm_gic_intr_eoi(&id);
}

void intr_init(void)
{
    excpt_inst_handle(ET_IRQ, irq_handler);

    /* init GIC */
    arm_gic_init(cpu_priv_mem);

    CPU_ENABLE_IRQ(true);
    CPU_ENABLE_FIQ(true);
}

void intr_mask(uint32_t id, bool mask)
{
    arm_gic_intr_enable(id, !mask);
}

void intr_inst_handle(uint32_t id, intr_handle handle)
{
    handler[id] = handle;
}

