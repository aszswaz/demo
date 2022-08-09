#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FILE_NAME "sparse-files.raw"
#define FILE_ERROR(expression) \
    if (expression) { \
        perror(FILE_NAME); \
        exit_code = EXIT_FAILURE; \
        goto finally; \
    }

int main() {
    char buf[BUFSIZ];
    int fd;
    int exit_code = 0;
    struct stat file_stat;
    size_t write_size = 0, current_write = 0;
    size_t buffer_size = 0, len;

    fd = open(FILE_NAME, O_WRONLY);
    FILE_ERROR(fd == -1);
    memset(&buf, 1, BUFSIZ);
    FILE_ERROR(stat(FILE_NAME, &file_stat));

    write_size = file_stat.st_size + (10 * 1024 * 1024);
    fprintf(stdout, "sparse file size: %ld mb, write size: %ld mb\n", file_stat.st_size / 1024 / 1024, write_size / 1024 / 1024);

    while (current_write < write_size) {
        buffer_size = (current_write + BUFSIZ) < write_size ? BUFSIZ : write_size - current_write;
        len = write(fd, buf, BUFSIZ);
        current_write += buffer_size;
        FILE_ERROR(len == -1);
    }

finally:
    if (fd != -1) close(fd);
    return exit_code;
}
