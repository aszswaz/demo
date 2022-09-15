#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

#define SOCK_PATH "server.sock"
#define SYSCALL_ERROR(expression) \
    if (expression) { \
        printf("%s %d: %s\n", __FILE_NAME__, __LINE__, strerror(errno)); \
        goto finally; \
    }

int main() {
    int sockfd = -1;
    int code;
    struct sockaddr_un addr;
    char buffer[BUFSIZ];
    socklen_t socklen;

    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    SYSCALL_ERROR(sockfd == -1);
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCK_PATH);
    code = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    SYSCALL_ERROR(code == -1);

    // Receive data from the client and get the client's address and port.
    socklen = sizeof(addr);
    code = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&addr, &socklen);
    SYSCALL_ERROR(code == -1);
    printf("client address: %s\n", addr.sun_path);
    printf("client message: ");
    fwrite(buffer, code, 1, stdout);
    printf("\n");
    // response message.
    code = sendto(sockfd, buffer, code, 0, (struct sockaddr *)&addr, sizeof(addr));
    SYSCALL_ERROR(code == -1);

finally:
    if (sockfd != -1) close(sockfd);
    return EXIT_SUCCESS;
}
