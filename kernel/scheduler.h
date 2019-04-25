#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

void scheduler_init(void);
void scheduler_start(void);

/*
 * do not call this function directly,
 * unless you know what you're doing
 */
void do_scheduling(void);

#endif
