#ifndef _THREAD_H_
#define _THREAD_H_

enum thread_stat
{
    TS_IDLE = 0,
    TS_INIT,
    TS_RUN,
    TS_WAIT,
    TS_RDY,

    TS_ALL
};

#define INVL_THREAD_HANDLE (NULL)

typedef struct thread* thread_t;
typedef uint32_t (*thread_entry)(uint32_t argc, void *argv[]);

struct thread
{
    char name[32];

    enum thread_stat stat;
    thread_entry entry;
    void *sp;
    uint8_t priority;
    uint32_t ticks;

    void *user;
    bool used;

    struct thread *next;
};

extern struct thread thread_pool[MAX_SUPPORT_TRHEAD];

void thread_init(void);
thread_t thread_create(char *name, thread_entry entry, uint8_t priority, void *user);
void thread_suspend(thread_t thread);
void thread_resume(thread_t thread);
enum thread_stat thread_get_stat(thread_t thread);
void thread_joint(thread_t thread);
void thread_destroy(thread_t thread);

#endif
