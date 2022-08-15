#include <pipeline.h>
#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>

int main() {
    pipeline *cmd;
    const char *line;

    // get user info
    struct passwd *uinfo = getpwuid(geteuid());
    if (!uinfo) {
        perror(NULL);
        return EXIT_FAILURE;
    }
    printf("login shell: %s\n", uinfo->pw_shell);

    // Create the pipeline of the external application, NULL indicates the end of parameter input.
    cmd = pipeline_new_command_args(uinfo->pw_shell, "-c", "echo 'Hello World' 1>&2", NULL);
    pipeline_want_out(cmd, -1);
    pipeline_start(cmd);
    line = pipeline_peekline(cmd);
    if (!strstr(line, "coding: UTF-8")) printf("Unicode text follows:0\n");

    while ((line = pipeline_readline(cmd))) printf("stdout: %s", line);

    printf("exit code: %d\n", pipeline_wait(cmd));

    return EXIT_SUCCESS;
}
