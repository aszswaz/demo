#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/un.h>

#define SYSCALL_ERROR(expression) \
    if (expression) { \
        printf("%s %d: %s\n", __FILE_NAME__, __LINE__, strerror(errno)); \
        goto finally; \
    }


#define SERVER_SOCK "server.sock"
#define CLIENT_SOCK "client.sock"

int main() {
    int code;
    int sockfd = -1;
    struct sockaddr_un saddr, caddr;
    socklen_t socklen = sizeof(struct sockaddr_un);
    const char *message = "Hello World";
    char buffer[BUFSIZ];

    saddr.sun_family = AF_UNIX;
    strcpy(saddr.sun_path, SERVER_SOCK);
    caddr.sun_family = AF_UNIX;
    strcpy(caddr.sun_path, CLIENT_SOCK);

    // The client must also hold a unix domain socket for bidirectional communication with the service.
    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    SYSCALL_ERROR(sockfd == -1);
    code = bind(sockfd, (struct sockaddr *)&caddr, sizeof(caddr));
    SYSCALL_ERROR(code == -1);

    code = sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&saddr, socklen);
    SYSCALL_ERROR(code == -1);
    code = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&saddr, &socklen);
    SYSCALL_ERROR(code == -1);
    printf("server response: ");
    fwrite(buffer, code, 1, stdout);
    printf("\n");

finally:
    if (sockfd != -1) close(sockfd);
    return EXIT_SUCCESS;
}
