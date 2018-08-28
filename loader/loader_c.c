typedef char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;

struct pc_uart_reg
{
    uint32_t DR;
    uint32_t SR;
    uint32_t resv_0[4];
    const uint32_t FR;
    uint32_t resv_1;
    uint32_t ILPR;
    uint32_t IBRD;
    uint32_t FBRD;
    uint32_t LCR_H;
    uint32_t CR;
    uint32_t IFLS;
    uint32_t IMSC;
    const uint32_t RIS;
    const uint32_t MIS;
    uint32_t ICR;
    uint32_t DMACR;
    uint32_t resv_2[13];
    uint32_t resv_3[4];
    uint32_t resv_4[976];
    uint32_t resv_5[4];
    const uint32_t PERIPHID0;
    const uint32_t PERIPHID1;
    const uint32_t PERIPHID2;
    const uint32_t PERIPHID3;
    const uint32_t CELLID0;
    const uint32_t CELLID1;
    const uint32_t CELLID2;
    const uint32_t CELLID3;
}__attribute__((packed));

static volatile struct pc_uart_reg * const uart0 = (volatile struct pc_uart_reg *)0x10009000;

static char str[] = {"Hello World From C!\n"};

void puts(char *s)
{
    while(*s)
    {
        while(uart0->FR & 0x08) ;
        uart0->DR = *s;
        s++;
    }
}

typedef void (*kernel_entry)(void);

kernel_entry load_kernel(void)
{
    volatile uint32_t *ptr;
    uint32_t lma_off;
    uint32_t *vma_addr;
    uint32_t img_size;
    uint32_t i;

    ptr = (volatile uint32_t *)0x00001000;
    lma_off = ptr[0];
    img_size = (ptr[1]+3)>>2;
    vma_addr = (uint32_t *)ptr[2];

    ptr = (volatile uint32_t *)(0x00001000+ptr[0]);

    for(i=0; i<img_size; i++)
    {
        vma_addr[i] = ptr[i];
    }

    return (kernel_entry)vma_addr;
}

void loader_start_c(void)
{
    volatile kernel_entry entry;

    puts(str);

    entry = load_kernel();
    entry();

    while(1) ;
}
