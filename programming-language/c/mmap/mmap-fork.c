#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <signal.h>

#define MEM_SIZE 32
#define FILE_ERROR(expression) \
    if (expression) { \
        code = EXIT_FAILURE; \
        goto finally; \
    }

static char running = 1;

/**
 * Random ascii characters.
 */
static void rand_string(char *ptr, size_t len) {
    memset(ptr, 0, len);
    const char min = 65, max = 90;
    int result;
    for (int i = 0; i < len; i++) {
        // Set a random seed.
        srand48(time(NULL));
        result = (rand() % (max - min + 1)) + min;
        ptr[i] = result;
    }
    printf("parent: %s\n", ptr);
}

void exit_hander() {
    running = 0;
}

void signal_exit(int sig) {
    exit_hander();
}

int main() {
    int code = EXIT_SUCCESS;
    char *addr;
    int fd;
    pid_t sub_pid;

    atexit(exit_hander);
    signal(SIGTERM, signal_exit);
    signal(SIGINT, signal_exit);
    signal(SIGKILL, signal_exit);

    printf("Allocate shared memory.\n");
    // MAP_ANONYMOUS represents the memory mapping, and there is no corresponding file.
    addr = mmap(NULL, MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    FILE_ERROR(addr == MAP_FAILED);
    sub_pid = fork();
    FILE_ERROR(sub_pid == -1);

    if (!sub_pid) {
        // child process.
        printf("child process: shared memory pointer: %p\n", addr);
        while (running) {
            printf("child process: %s\n", addr);
            sleep(7);
        }
    } else {
        // parent process.
        printf("parent: shared memory pointer: %p\n", addr);
        while (running) {
            rand_string(addr, MEM_SIZE);
            sleep(5);
        }
    }

finally:
    printf("finally\n");
    if (addr != MAP_FAILED) munmap(addr, MEM_SIZE);
    return code;
}
