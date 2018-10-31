#ifndef _GIC_H_
#define _GIC_H_

#define INVLD_INTR_ID (1023)

struct arm_gic_intr_id
{
    union
    {
        struct
        {
            uint32_t int_id:10;
            uint32_t cpu_id:3;
            uint32_t rsv:19;
        };
        uint32_t val;
    };
};

void arm_gic_init(uint8_t *base);
void arm_gic_intr_enable(uint8_t id, bool enable);
void arm_gic_intr_ack(struct arm_gic_intr_id *id);
void arm_gic_intr_eoi(struct arm_gic_intr_id *id);

#endif

