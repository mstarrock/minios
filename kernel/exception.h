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

typedef void (*excpt_handle)(void);

void excpt_init(void *vector);
void excpt_inst_handle(enum excpt_type type, excpt_handle func);

#endif
