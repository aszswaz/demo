#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <arpa/inet.h>

#define SYSCALL_ERROR(expression) \
    if (expression) { \
        printf("%s %d: %s", __FILE_NAME__, __LINE__, strerror(errno)); \
        goto finally; \
    }

int main() {
    struct sockaddr_in saddr;
    int socketfd = -1;
    int code;
    const char *message = "Hello World";
    socklen_t socklen = sizeof(saddr);
    char buff[BUFSIZ];

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8080);
    saddr.sin_addr.s_addr = INADDR_ANY;

    socketfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    SYSCALL_ERROR(socketfd == -1);

    code = sendto(socketfd, message, strlen(message), 0, (struct sockaddr *)&saddr, socklen);
    SYSCALL_ERROR(code == -1);

    memset(buff, 0, sizeof(buff));
    code = recvfrom(socketfd, buff, sizeof(buff), 0, (struct sockaddr *)&saddr, &socklen);
    SYSCALL_ERROR(code == -1);
    fprintf(stdout, "sever message: %s\n", buff);

finally:
    if (socketfd != -1) close(socketfd);
    return EXIT_SUCCESS;
}
