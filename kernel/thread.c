#include "config.h"
#include "types.h"
#include "cpu.h"
#include "spinlock.h"

#include "misc.h"
#include "thread.h"

struct thread thread_pool[MAX_SUPPORT_TRHEAD];

static spinlock_t thread_global_lock;

void thread_init(void)
{
    uint32_t idx;

    for(idx=0; idx<MAX_SUPPORT_TRHEAD-1; idx++)
    {
        thread_pool[idx].next = &thread_pool[idx+1];
    }

    thread_pool[MAX_SUPPORT_TRHEAD-1].next = &thread_pool[0];
}

thread_t thread_create(
        char *name,
        thread_entry entry,
        uint8_t priority,
        void *user)
{
    uint32_t idx=0;
    uint32_t flag;
    struct thread *t = NULL;

    do
    {
        spinlock_lock_save_irq(&thread_global_lock, flag);

        /* find empty thread slot */
        for(idx=0; idx<MAX_SUPPORT_TRHEAD; idx++)
        {
            if(false == thread_pool[idx].used)
            {
                t = &thread_pool[idx];
                t->used = true;

                break;
            }
        }

        spinlock_unlock_restore_irq(&thread_global_lock, flag);

        if(NULL == t)
            break;

        /* initialize thread slot */
        strncpy(t->name, name, 31);
        t->stat = TS_INIT;
        t->entry = entry;
        t->priority = priority;
        t->ticks = THREAD_TIME_SLICE;
        t->user = user;

        /* allocate stack for new thread */
        {
            extern uint32_t _mem_pool_start[];
            uint32_t spsr = 0;
            uint32_t *stack;

            spsr = CM_SUV | (0x1<<8);

            stack = _mem_pool_start+((idx+1)*0x400)-17;
            stack[0] = (uint32_t)&stack[1];
            stack[15] = (uint32_t)entry;
            stack[16] = spsr;
            t->sp = stack;
        }

        /* binding necessary kernel objects to thread */

        /* put thread into ready state for scheduling */
        t->stat = TS_RDY;

        return (thread_t)t;
    }while(0);

    if(NULL != t)
    {
        /* free related kernel objects/resources */

        /* free the slot */
        t->used = false;
    }

    return INVL_THREAD_HANDLE;
}

void thread_suspend(thread_t thread)
{

}

void thread_resume(thread_t thread)
{

}

enum thread_stat thread_get_stat(thread_t thread)
{
    return TS_RDY;
}

void thread_joint(thread_t thread)
{

}

void thread_destroy(thread_t thread)
{

}

