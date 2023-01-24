#include <stdio.h>
#include <stdlib.h>

int main() {
    char buff[BUFSIZ];
    FILE *pipe;
    int code;

    pipe = popen("echo 'Hello World' 1>&2", "w");
    if (!pipe) {
        perror("echo");
        return EXIT_FAILURE;
    }
    fread(buff, BUFSIZ, 1, pipe);
    fprintf(stdout, "%s", buff);
    code = pclose(pipe);
    if (code == -1) {
        perror("echo");
        return EXIT_FAILURE;
    }

    return code;
}
