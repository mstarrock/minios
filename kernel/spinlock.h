#ifndef _SPINLOCK_H_
#define _SPINLOCK_H_

typedef uint32_t spinlock_t;

bool spinlock_lock(spinlock_t lock);
bool spinlock_unlock(spinlock_t lock);
bool spinlock_lock_save_irq(spinlock_t lock, uint32_t flags);
bool spinlock_unlock_restore_irq(spinlock_t lock, uint32_t flags);

#endif
