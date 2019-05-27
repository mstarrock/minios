#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

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

typedef void (*intr_handle)(uint32_t id);

void intr_init(void);
void intr_mask(uint32_t id, bool mask);
void intr_inst_handle(uint32_t id, intr_handle handle);

#endif
