#ifndef _CPU_H_
#define _CPU_H_

#include "types.h"

#define CM_SYS (31)
#define CM_UND (27)
#define CM_HYP (26)
#define CM_ABT (23)
#define CM_MON (22)
#define CM_SUV (19)
#define CM_IRQ (18)
#define CM_FIQ (17)
#define CM_USR (16)

/* private memory region address */
extern uint8_t *cpu_priv_mem;

#endif
