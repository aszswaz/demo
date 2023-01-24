#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void signal_handler(int code) {
    switch(code) {
    case SIGABRT:
        printf("SIGABRT\n");
        break;
    case SIGALRM:
        printf("SIGALRM\n");
        break;
    case SIGBUS:
        printf("SIGBUS\n");
        break;
    case SIGCHLD:
        printf("SIGCHLD\n");
        break;
    case SIGCONT:
        printf("SIGCONT\n");
        break;
    case SIGFPE:
        printf("SIGFPE\n");
        break;
    case SIGHUP:
        printf("SIGHUP\n");
        break;
    case SIGILL:
        printf("SIGILL\n");
        break;
    case SIGINT:
        printf("SIGINT\n");
        break;
    case SIGKILL:
        printf("SIGKILL\n");
        break;
    case SIGPIPE:
        printf("SIGPIPE\n");
        break;
    case SIGPOLL:
        printf("SIGPOLL\n");
        break;
    case SIGPROF:
        printf("SIGPROF\n");
        break;
    case SIGQUIT:
        printf("SIGQUIT\n");
        break;
    case SIGSEGV:
        printf("SIGSEGV\n");
        break;
    case SIGSTOP:
        printf("SIGSTOP\n");
        break;
    case SIGSYS:
        printf("SIGSYS\n");
        break;
    case SIGTERM:
        printf("SIGTERM\n");
        break;
    case SIGTRAP:
        printf("SIGTRAP\n");
        break;
    case SIGTTIN:
        printf("SIGTTIN\n");
        break;
    case SIGTTOU:
        printf("SIGTTOU\n");
        break;
    case SIGURG:
        printf("SIGURG\n");
        break;
    case SIGUSR1:
        printf("SIGUSR1\n");
        break;
    case SIGUSR2:
        printf("SIGUSR2\n");
        break;
    case SIGVTALRM:
        printf("SIGALRM\n");
        break;
    case SIGXCPU:
        printf("SIGXCPU\n");
        break;
    case SIGXFSZ:
        printf("SIGXFSZ\n");
        break;
    default:
        printf("Unknown signal.");
    }
    exit(0);
}

int main() {

    pid_t process = fork();

    signal(SIGABRT, signal_handler);
    signal(SIGALRM, signal_handler);
    signal(SIGBUS, signal_handler);
    signal(SIGCHLD, signal_handler);
    signal(SIGCONT, signal_handler);
    signal(SIGFPE, signal_handler);
    signal(SIGHUP, signal_handler);
    signal(SIGILL, signal_handler);
    signal(SIGINT, signal_handler);
    signal(SIGKILL, signal_handler);
    signal(SIGPIPE, signal_handler);
    signal(SIGPOLL, signal_handler);
    signal(SIGPROF, signal_handler);
    signal(SIGQUIT, signal_handler);
    signal(SIGSEGV, signal_handler);
    signal(SIGSTOP, signal_handler);
    signal(SIGSYS, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGTRAP, signal_handler);
    signal(SIGTTIN, signal_handler);
    signal(SIGTTOU, signal_handler);
    signal(SIGURG, signal_handler);
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    signal(SIGVTALRM, signal_handler);
    signal(SIGXCPU, signal_handler);
    signal(SIGXFSZ, signal_handler);

    if (process == 0) {
        while(1) {
            sleep(1);
        }
    } else if (process > 0) {
        sleep(5);
    }

    return EXIT_SUCCESS;
}
