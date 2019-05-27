#include "config.h"
#include "types.h"
#include "interrupt.h"

#include "spinlock.h"

bool spinlock_lock(spinlock_t *lock)
{
    unsigned int tmp;

    asm volatile("loop:\n\t"
                 "ldrex %0, %1\n\t"
                 "cmp %0, #0\n\t"
                 "strexeq %0, r0, %1\n\t"
                 "cmpeq %0, #0\n\t"
                 "bne loop\n\t"
                 : "=&r" (tmp)
                 : "m" (*lock)
                 : "cc");
}

bool spinlock_unlock(spinlock_t *lock)
{
    unsigned int tmp;

    asm volatile("mov %0, #0\n\t"
                 "dmb\n\t"
                 "str %0, %1"
                 : "=&r" (tmp)
                 : "m" (*lock));
}

bool spinlock_lock_save_irq(spinlock_t *lock, uint32_t flags)
{
#if (SMP == 1)
    spinlock_lock(lock);
#endif
    CPU_ENABLE_IRQ(false)
    CPU_ENABLE_FIQ(false)
    return true;
}

bool spinlock_unlock_restore_irq(spinlock_t *lock, uint32_t flags)
{
    CPU_ENABLE_IRQ(true)
    CPU_ENABLE_FIQ(true)
#if (SMP == 1)
    spinlock_unlock(lock);
#endif
    return true;
}

