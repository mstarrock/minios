#ifndef _CONFIG_H_
#define _CONFIG_H_

/*
 * When this config set to 1, then all exception initailizing and
 * handling related implementations will directly in C language.
 * Assembly code will only has a handler skeleton that doing
 * infinite loop.
 */
#ifndef EXCPT_VECTOR_IN_C
#define EXCPT_VECTOR_IN_C (1)
#endif

/*
 * When this config set to 1, all exception handle will share
 * stack with supervisor mode. This could enhance the readability
 * when doing debug backtrace.
 */
#ifndef USE_SUPV_STACK
#define USE_SUPV_STACK (1)
#endif

/*
 * Specified whether the kernel will running in SMP environment.
 */
#ifndef SMP
#define SMP (0)
#endif

/*
 * Specified total number of cores that kernel will running on.
 */
#ifndef NUM_CPU_CORES
#define NUM_CPU_CORES (1)
#endif

/*
 * Maximum supported thread
 */
#ifndef MAX_SUPPORT_TRHEAD
#define MAX_SUPPORT_TRHEAD (1024)
#endif

/*
 * Maximum supported thread
 */
#ifndef THREAD_TIME_SLICE
#define THREAD_TIME_SLICE (10)
#endif

#endif
