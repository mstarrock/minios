#ifndef _CONFIG_H_
#define _CONFIG_H_

/*
 * When this config set to 1, then all exception initailizing and
 * handling related implementations will directly in C language.
 * Assembly code will only has a handler skeleton that doing
 * infinite loop.
 */
#define EXCPT_VECTOR_IN_C (1)

/*
 * When this config set to 1, all exception handle will share
 * stack with supervisor mode. This could enhance the readability
 * when doing debug backtrace.
 */
#define USE_SUPV_STACK (1)

#endif
