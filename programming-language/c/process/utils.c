#include "utils.h"
#include <pwd.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

const char *login_shell() {
    uid_t uid;
    struct passwd *uinfo;

    uid = geteuid();
    uinfo = getpwuid(uid);
    if (!uinfo) {
        perror(NULL);
        exit(EXIT_FAILURE);
        return NULL;
    }
    return uinfo->pw_shell;
}
