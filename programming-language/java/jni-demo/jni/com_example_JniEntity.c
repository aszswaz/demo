#include "com_example_JniEntity.h"
#include <stdio.h>
#include <unistd.h>

JNIEXPORT void JNICALL Java_com_example_JniEntity_fork (JNIEnv *, jclass) {
    pid_t sub_pid = fork();
    if (sub_pid == 0) {
        // The child process sleeps to avoid resource contention.
        sleep(5);
    } else {
        printf("sub pid: %ld\n", sub_pid);
    }
}
