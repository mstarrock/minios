#include "types.h"

#include "gic.h"

struct gic_dist_reg
{
    uint32_t ICDDCR;
    uint32_t ICDICTR;
    uint32_t ICDIIDR;
    uint32_t resv_0[29];
    uint32_t ICDISRn[8];
    uint32_t resv_1[24];
    uint32_t ICDISERn[8];
    uint32_t resv_2[24];
    uint32_t ICDICERn[8];
    uint32_t resv_3[24];
    uint32_t ICDISPRn[32];
    uint32_t ICDICPRn[8];
    uint32_t resv_4[24];
    uint32_t ICDABRn[8];
    uint32_t resv_5[56];
    uint32_t ICDIPTR[64];
    uint32_t resv_6[192];
    uint32_t ICDIPTRn[64];
    uint32_t resv_7[192];
    uint32_t ICDICFRn[16];
    uint32_t resv_8[48];
    uint32_t ICPPISR;
    uint32_t ICSPISRn[7];
    uint32_t resv_9[120];
    uint32_t ICDSGIR;
    uint32_t resv_10[51];
    uint32_t ICPIDR0;
    uint32_t ICPIDR1;
    uint32_t ICPIDR2;
    uint32_t ICPIDR3;
    uint32_t ICPIDR4;
    uint32_t ICPIDR5;
    uint32_t ICPIDR6;
    uint32_t ICPIDR7;
    uint32_t ICCIDR0;
    uint32_t ICCIDR1;
    uint32_t ICCIDR2;
    uint32_t ICCIDR3;
}__attribute__((packed));

struct gic_proc_intf_reg
{
    uint32_t ICCICR;
    uint32_t ICCPMR;
    uint32_t ICCBPR;
    uint32_t ICCIAR;
    uint32_t ICCEOIR;
    uint32_t ICCRPR;
    uint32_t ICCHPIR;
    uint32_t ICCABPR;
    uint32_t resv_0[55];
    uint32_t ICCIDR;
}__attribute__((packed));

static struct gic_dist_reg *intr_dist;
static struct gic_proc_intf_reg *intr_ctrl;

void arm_gic_init(uint8_t *base)
{
    uint8_t i;

    intr_ctrl = (struct gic_proc_intf_reg *)&base[0x100];
    intr_dist = (struct gic_dist_reg *)&base[0x1000];
    
    intr_dist->ICDDCR = 0x0;
    intr_ctrl->ICCICR = 0x0;
    /* config gic distributor */

    for(i=0; i<8; i++)
    {
        intr_dist->ICDICPRn[i] = 0xffffffff;
        intr_dist->ICDICERn[i] = 0xffffffff;
        intr_dist->ICDIPTR[i] = 0;
    }

    intr_dist->ICDDCR = 0x3;

    /* config processor interface */
    intr_ctrl->ICCPMR = 0xf;

    intr_ctrl->ICCICR = 0x3;
}

void arm_gic_intr_enable(uint8_t id, bool enable)
{
    uint32_t val;

    if(enable)
    {
        val = (1<<(id%32));
        intr_dist->ICDISERn[id/32] = val;
    }
    else
    {
        val = (1<<(id%32));
        intr_dist->ICDICERn[id/32] = val;
    }
}

void arm_gic_intr_ack(struct arm_gic_intr_id *id)
{
    id->val = intr_ctrl->ICCIAR;
}

void arm_gic_intr_eoi(struct arm_gic_intr_id *id)
{
    intr_ctrl->ICCEOIR = id->val;
}

