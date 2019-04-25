#ifndef _TIMER_H_
#define _TIMER_H_

typedef uint32_t timer_t;

struct timer_cfg
{
    bool auto_start;
    uint32_t interval;
};

typedef void (*timer_cb)(timer_t timer);

void timer_init(uint8_t *base);
timer_t timer_open(struct timer_cfg *cfg);
void timer_enable(timer_t timer, bool enable);
void timer_inst_cb(timer_t timer, timer_cb cb);

#endif
