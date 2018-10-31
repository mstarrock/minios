#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

typedef void (*intr_handle)(uint32_t id);

void intr_init(void);
void intr_mask(uint32_t id, bool mask);
void intr_inst_handle(uint32_t id, intr_handle handle);

#endif
