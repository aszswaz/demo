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

    if (!access(FILE_NAME, F_OK)) {
        // file exists
        FILE_ERROR(remove(FILE_NAME));
    }

    /*
     * O_CREAT：Create the file if it does not exist.
     * O_WRONLY: Open for writing only.
     * When creating a file, set file permissions:
     * S_IRUSR: Readable by the file owner.
     * S_IWUSR: File owner writable.
     * S_IRGRP: Readable by users in the same group as the owner of the file.
     * S_IROTH: Readable by other users.
     * S_IRWXU: This is equivalent to ‘(S_IRUSR | S_IWUSR | S_IXUSR)’.
     * If no permission is set, the default value is S_IRWXU.
     */
    fd = open(FILE_NAME, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    FILE_ERROR(fd == -1);
    // In the file metadata, set the file size.
    FILE_ERROR(ftruncate(fd, 50 * 1024 * 1024));
    memset(&buf, 1, BUFSIZ);
    FILE_ERROR(stat(FILE_NAME, &file_stat));

    write_size = file_stat.st_size - (10 * 1024 * 1024);
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
