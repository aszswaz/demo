#include "thread_pool.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <stdio.h>

#define PTHREAD_ERROR(expression) \
    code = expression; \
    if (code) { \
        errno = code; \
        goto error; \
    }

#define POOL_SIZE 4

typedef struct task {
    thread_run run;
    void *args;
    struct task *next;
} task_t;

/**
 * Thread Pool
 */
struct thread_pool {
    bool shutdown;
    pthread_t threads[POOL_SIZE];
    pthread_cond_t tasks_ready;
    pthread_mutex_t tasks_lock;
    task_t *task_head;
    task_t *task_tail;
};

/**
 * The start entry function of the thread.
 */
static void *thread_pool_poll(void *args) {
    int code;
    const char *errmsg;
    task_t *task;
    thread_pool_t *self = (thread_pool_t *)args;

    while (!self->shutdown) {
        PTHREAD_ERROR(pthread_mutex_lock(&self->tasks_lock));
        if (!self->task_head) {
            PTHREAD_ERROR(pthread_cond_wait(&self->tasks_ready, &self->tasks_lock));
        }
        task = self->task_head;
        if (task) {
            self->task_head = task->next;
            PTHREAD_ERROR(pthread_mutex_unlock(&self->tasks_lock));
            task->run(task->args);
            free(task);
        } else {
            PTHREAD_ERROR(pthread_mutex_unlock(&self->tasks_lock));
            continue;
        }
    }

    return NULL;
error:
    errmsg = strerror(code);
    fprintf(stderr, "%s %d: %s\n", __FILE_NAME__, __LINE__, errmsg);
    return NULL;
}

static void thread_pool_free(thread_pool_t *self) {
    task_t *next, *intermediate;

    next = self->task_head;

    while (next) {
        intermediate = next->next;
        free(next);
        next = intermediate;
    }

    pthread_cond_destroy(&self->tasks_ready);
    pthread_mutex_destroy(&self->tasks_lock);
    free(self);
}

thread_pool_t *thread_pool_new() {
    thread_pool_t *self;
    int code;

    self = malloc(sizeof(thread_pool_t));
    if (!self) goto error;
    memset(self, 0, sizeof(thread_pool_t));

    PTHREAD_ERROR(pthread_cond_init(&self->tasks_ready, NULL));
    PTHREAD_ERROR(pthread_mutex_init(&self->tasks_lock, NULL));

    for (uint8_t i = 0; i < POOL_SIZE; i++) {
        PTHREAD_ERROR(pthread_create(&self->threads[i], NULL, thread_pool_poll, self));
    }

    return self;
error:
    thread_pool_free(self);
    return NULL;
}

void thread_pool_shutdown(thread_pool_t *self) {
    if (self->shutdown) return;
    self->shutdown = 1;

    pthread_mutex_lock(&self->tasks_lock);
    pthread_cond_broadcast(&self->tasks_ready);
    pthread_mutex_unlock(&self->tasks_lock);

    for (uint8_t i = 0; i < POOL_SIZE; i++) {
        pthread_join(self->threads[i], NULL);
    }

    thread_pool_free(self);
}

int thread_pool_execute(thread_pool_t *self, thread_run run, void *args) {
    task_t *task, *task_head;
    int code;

    if (!run) return EINVAL;

    task = malloc(sizeof(task_t));
    if (!task) return errno;
    memset(task, 0, sizeof(task_t));

    task->run = run;
    task->args = args;

    PTHREAD_ERROR(pthread_mutex_lock(&self->tasks_lock));
    task_head = self->task_head;
    if (task_head)
        self->task_tail->next = task;
    else
        self->task_head = task;
    self->task_tail = task;

    PTHREAD_ERROR(pthread_cond_signal(&self->tasks_ready));
    PTHREAD_ERROR(pthread_mutex_unlock(&self->tasks_lock));
    return 0;
error:
    return code;
}
