#include <stdio.h>
#include "../thread_pool.h"
#include <pthread.h>
#include <unistd.h>

#define STAND_ERROR(expression) \
    if (expression) { \
        perror(__FILE_NAME__); \
        return -1; \
    }

void test_run(void *data) {
    pthread_t thread_id = pthread_self();
    printf("thread id: 0x%lX ====================================next====================================\n", thread_id);
    for (int i = 0; i < 12; i++) {
        printf("thread id: 0x%lX, i: %d\n", thread_id, i);
        sleep(1);
    }
}

int main() {
    thread_pool_t *thpool;

    thpool = thread_pool_new();
    STAND_ERROR(!thpool);

    for (int i = 0; i < 10; i++) thread_pool_execute(thpool, test_run, NULL);
    sleep(60);
    for (int i = 0; i < 10; i++) thread_pool_execute(thpool, test_run, NULL);
    thread_pool_shutdown(thpool);
}
