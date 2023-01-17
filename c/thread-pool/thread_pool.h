#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <stdint.h>

struct thread_pool;
typedef struct thread_pool thread_pool_t;
// The entry function for the thread in the thread pool to execute the task.
typedef void (*thread_run)(void *);

/**
 * Create a thread pool.
 *
 * @param total The number of threads in the thread pool.
 */
thread_pool_t *thread_pool_new();

void thread_pool_shutdown(thread_pool_t *self);

int thread_pool_execute(thread_pool_t *self, thread_run run, void *args);

#endif
