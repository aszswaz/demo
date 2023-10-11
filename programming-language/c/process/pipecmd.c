#include <stdlib.h>
#include <pipeline.h>
#include "utils.h"

int main() {
    pipecmd *cmd;
    const char *shell;

    shell = login_shell();
    printf("login shell: %s\n", shell);
    cmd = pipecmd_new_args(shell, "-c", "echo 'Hello World' 1>&2", NULL);
    pipecmd_exec(cmd);

    pipecmd_free(cmd);
    return EXIT_SUCCESS;
}
