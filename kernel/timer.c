#include "types.h"
#include "interrupt.h"
#include "gic.h"

#include "timer.h"

struct global_timer_reg
{
    uint32_t CR_LO;
    uint32_t CR_HI;
    uint32_t CR;
    uint32_t ISR;
    uint32_t CVR_LO;
    uint32_t CVR_HI;
    uint32_t AIR;
};

struct private_timer_reg
{
    uint32_t LR;
    uint32_t CR;
    uint32_t CTRL;
    uint32_t ISR;
};

static volatile struct global_timer_reg *gt_reg;
static volatile struct private_timer_reg *pt_reg;
static timer_cb timer_user_cb;

static void timer_intr_cb(uint32_t id)
{
    if(timer_user_cb)
        timer_user_cb(0);
}

void timer_init(uint8_t *base)
{
    uint32_t val;
    gt_reg = (struct global_timer_reg *)&base[0x200];
    pt_reg = (struct private_timer_reg *)&base[0x600];

    intr_mask(27, false);
    intr_inst_handle(27, timer_intr_cb);
}

timer_t timer_open(struct timer_cfg *cfg)
{
    gt_reg->CR = 0x0;
    gt_reg->CR_LO = 0x0;
    gt_reg->CR_HI = 0x0;
    gt_reg->CVR_LO = 0x1000000;
    gt_reg->CVR_HI = 0x0;
    gt_reg->AIR = 0x1000000;
    gt_reg->ISR = 0x1;
#if 0
    // private timer
    pt_reg->LR = 0xffffffff;
    pt_reg->CR = 0xffffffff;
    pt_reg->CTRL = 0x5;
#endif
}

void timer_enable(timer_t timer, bool enable)
{
    if(enable)
        gt_reg->CR = 0xf;
    else
        gt_reg->CR = 0x0;
}

void timer_inst_cb(timer_t timer, timer_cb cb)
{
    timer_user_cb = cb;
}

