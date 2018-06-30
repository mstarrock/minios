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
}__attribute__((packed));

static volatile struct pc_uart_reg * const uart0 = (volatile struct pc_uart_reg *)0x10009000;

static char str[] = {"Hello World From C!\n"};

void puts(char *s)
{
    while(*s)
    {
        uart0->DR = *s;
        s++;
    }
}

void loader_start_c(void)
{
    puts(str);

    while(1) ;
}
