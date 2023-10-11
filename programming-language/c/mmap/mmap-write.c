#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <signal.h>

#define FILE_NAME "memory.bin"
#define FILE_SIZE 32
#define CONTENT "Hello World"
// File Permissions.
#define PERMISSION S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
// Open the file in read-write mode, or create the file if it does not exist.
#define FILE_MODE O_CREAT | O_RDWR
#define FILE_ERROR(expression) \
    if (expression) { \
        perror(FILE_NAME); \
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
    printf("%s\n", ptr);
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

    atexit(exit_hander);
    signal(SIGTERM, signal_exit);
    signal(SIGINT, signal_exit);
    signal(SIGKILL, signal_exit);

    // Open or create a file in the `/dev/shm` directory.
    fd = shm_open(FILE_NAME, FILE_MODE, PERMISSION);
    FILE_ERROR(fd == -1);

    /*
     * If the file size in the file metadata is smaller than the required shared memory size,
     * it will cause the shared memory write to fail, resulting in a bit segmentation fault.
     * Therefore, we need to modify the file size in the metadata through the `ftruncate` function, commonly known as `hole punching`.
     */
    FILE_ERROR(ftruncate(fd, FILE_SIZE));

    printf("Allocate shared memory.\n");
    // Allocate shared memory.
    addr = mmap(NULL, FILE_SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
    FILE_ERROR(addr == MAP_FAILED);
    printf("shared memory pointer: %p\n", addr);

    while (running) {
        rand_string(addr, FILE_SIZE);
        sleep(5);
    }

finally:
    printf("finally\n");
    if (fd != -1) {
        close(fd);
        shm_unlink(FILE_NAME);
    }
    if (addr != MAP_FAILED) munmap(addr, FILE_SIZE);
    return code;
}
