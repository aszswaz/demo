#include <sys/stat.h>
#include <sys/statvfs.h>
#include <stdio.h>
#include <math.h>

#define FILE_NAME "sparse-files.raw"

int main() {
    struct stat statbuf;
    struct statvfs statvfsbuf;

    if (stat(FILE_NAME, &statbuf)) {
        perror(FILE_NAME);
        return 1;
    }

    if (statvfs(FILE_NAME, &statvfsbuf)) {
        perror(FILE_NAME);
        return 1;
    }

    printf("ls file size: %ld mb\n", statbuf.st_size / 1024 / 1024);
    // The file will be cut into several 512B blocks, usually, st_size = st_blocks * 512, but if the file has holes, then st_size > st_blocks * 512.
    printf("du file size: %d mb\n", (int) ceil(statbuf.st_blocks * 512.0 / 1024.0 / 1024.0));

    return 0;
}
