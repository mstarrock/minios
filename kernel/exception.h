#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

enum excpt_type
{
    ET_UND = 0,
    ET_HYP,
    ET_ABT,
    ET_IRQ,
    ET_FIQ,

    ET_ALL
};

#if EXCPT_VECTOR_IN_C
#define EXCPT_ENTRY __attribute__((naked)) static

#if USE_SUPV_STACK
#define EXCPT_START(x) do { \
        asm volatile("sub lr, lr, #"#x"\n\t" \
            "srsdb sp!, #19\n\t" \
            "cps #19\n\t" \
            "stmdb sp!, {r0-r12,r14}\n\t" \
            "add fp, sp, #0\n\t"); \
        }while(0)
#else
#define EXCPT_START(x) do { \
        asm volatile("sub lr, lr, #"#x"\n\t" \
        "srsdb sp!, #27\n\t" \
        "stmdb sp!, {r0-r12,r14}\n\t" \
        "add fp, sp, #0\n\t"); \
        }while(0)
#endif

#define EXCPT_END() do { \
        asm volatile("add sp, fp, #0\n\t" \
        "ldmia sp!, {r0-r12,r14}\n\t" \
        "rfeia sp!\n\t"); \
        }while(0)
#else
#define EXCPT_ENTRY
#define EXCPT_START(x)
#define EXCPT_END()
#endif

typedef void (*excpt_handle)(void);

void excpt_init(void *vector);
void excpt_inst_handle(enum excpt_type type, excpt_handle func);

#endif
