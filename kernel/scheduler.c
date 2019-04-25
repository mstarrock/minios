#include "config.h"
#include "types.h"
#include "cpu.h"
#include "timer.h"
#include "misc.h"
#include "thread.h"

#include "exception.h"
#include "scheduler.h"

static timer_t tick_timer;
static thread_t hidle_thread = INVL_THREAD_HANDLE;
static thread_t huser_main_thread = INVL_THREAD_HANDLE;
static struct thread *current_thread[NUM_CPU_CORES];

static uint32_t idle_thread(uint32_t argc, void *argv[]);
uint32_t main(uint32_t argc, void *argv[]);

static uint8_t get_cpu_id(void)
{
    return 0;
}

static struct thread *get_next_thread(void)
{
    uint8_t cpu_id;
    struct thread *current;
    struct thread *next;

    cpu_id = 0;
    current = current_thread[cpu_id];

    next = current->next;
    while(next != current)
    {
        if((true == next->used) &&
           (TS_RDY == next->stat))
            break;

        next = next->next;
    }

    return next;
}

__attribute__((naked)) void do_scheduling(void)
{
    register uint8_t cpu_id;
    register uint8_t priority = 0xff;
    register struct thread *current;
    register struct thread *next;

    cpu_id = get_cpu_id();
    current = current_thread[cpu_id];

    if(0 == --current->ticks)
    {
        next = get_next_thread();
        next->ticks = THREAD_TIME_SLICE;

        if(next != current)
        {
            /* save context of from thread */
            asm volatile("push {fp}\n\t"
                         "str sp, %0\n\t"
                       : "=m" (current->sp));

            current->stat = TS_RDY;

            /* restore context of to thread */
            asm volatile("ldr sp, %0\n\t"
                         "pop {fp}\n\t"
                       :
                       : "m" (next->sp));

            next->stat = TS_RUN;
            current_thread[cpu_id] = next;
        }
    }

    EXCPT_END();
}

static uint32_t idle_thread(uint32_t argc, void *argv[])
{
    static uint32_t cnt=0;

    while(1)
    {
        cnt++;

        if(cnt == 0x100000)
        {
            puts("idle.\n");
            cnt = 0;
        }
    }
}

uint32_t main(uint32_t argc, void *argv[])
{
    static uint32_t cnt=0;

    while(1)
    {
        cnt++;

        if(cnt == 0x100000)
        {
            puts("main.\n");
            cnt = 0;
        }
    }
}

#if 0
static uint32_t thread_wrapper(struct thread *t)
{
    t->entry(0, NULL);
    while(1) ;
}
#endif

void scheduler_init(void)
{
    struct timer_cfg cfg;

    /* init thread */
    thread_init();

    /* create idle thread with lowest priority */
    hidle_thread = thread_create("idle", idle_thread, 0xfe, NULL);
    if(INVL_THREAD_HANDLE == hidle_thread)
    {
        return;
    }

    /* create thread for user program */
    huser_main_thread = thread_create("user_main", main, 0x80, NULL);
    if(INVL_THREAD_HANDLE == huser_main_thread)
    {
        return;
    }

    /* create tick timer */
    cfg.auto_start = false;
    cfg.interval = 0x100000;
    tick_timer = timer_open(&cfg);
}

void scheduler_start(void)
{
    uint8_t cpu_id;
    struct thread *t = (struct thread *)huser_main_thread;

    cpu_id = get_cpu_id();
    current_thread[cpu_id] = t;

    /* start system tick timer */
    timer_enable(tick_timer, true);

    /* jump to user main thread */
    t->stat = TS_RUN;
    asm volatile("ldr sp, %0\n\t"
            "pop {fp}\n\t"
            "ldmia sp!, {r0-r12,r14}\n\t"
            "rfeia sp!\n\t"
            :
            : "m" (t->sp));

    while(1) ;
}

