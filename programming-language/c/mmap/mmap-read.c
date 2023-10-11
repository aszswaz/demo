#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

#define FILE_NAME "memory.bin"
#define FILE_SIZE 32
#define CONTENT "Hello World"
#define PERMISSION S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
#define FILE_MODE O_RDONLY
#define FILE_ERROR(expression) \
    if (expression) { \
        perror(FILE_NAME); \
        code = EXIT_FAILURE; \
        goto finally; \
    }

static int running = 1;

void exit_hander() {
    running = 0;
}

void signal_exit(int sig) {
    exit_hander();
}

int main() {
    char *buf;
    int fd;
    int code = EXIT_SUCCESS;

    atexit(exit_hander);
    signal(SIGINT, signal_exit);
    signal(SIGTERM, signal_exit);
    signal(SIGKILL, signal_exit);

    fd = shm_open(FILE_NAME, FILE_MODE, PERMISSION);
    FILE_ERROR(fd == -1);

    // Create a memory map to an existing file.
    buf = mmap(NULL, FILE_SIZE, PROT_READ, MAP_SHARED, fd, 0);
    FILE_ERROR(buf == MAP_FAILED);
    printf("shared memory pointer: %p\n", buf);

    while (running) {
        printf("%s\n", buf);
        sleep(5);
    }

finally:
    printf("finally");
    if (fd != -1) close(fd);
    if (buf != MAP_FAILED) munmap(buf, FILE_SIZE);
    return code;
}
