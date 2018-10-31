#include "config.h"
#include "types.h"
#include "timer.h"

#include "scheduler.h"

extern void puts(char *s);

static void tick_timer_cb(timer_t timer)
{
    static uint32_t cnt = 0;
    if(cnt == 1000000)
    {
        puts("tick.\n");
        cnt = 0;
    }
    else
    {
        cnt++;
    }
}

void scheduler_init(void)
{
    timer_t tick_timer;
    struct timer_cfg cfg;

    cfg.auto_start = false;
    tick_timer = timer_open(&cfg);

    timer_inst_cb(tick_timer, tick_timer_cb);
    timer_enable(tick_timer, true);
}

void scheduler_start(void)
{
    puts("scheduler start.\n");
    while(1) ;
}

