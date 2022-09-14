#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SYSCALL_ERROR(expression) \
    if (expression) { \
        printf("%s %d: %s\n", __FILE_NAME__, __LINE__, strerror(errno)); \
        goto finally; \
    }

int main() {
    struct sockaddr_in addr;
    int socketfd = -1, clientfd = -1;
    socklen_t socklen = sizeof(addr);
    char buff[BUFSIZ];

    int code;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8080);
    addr.sin_family = AF_INET;

    socketfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    SYSCALL_ERROR(socketfd == -1);

    code = bind(socketfd, (struct sockaddr *)&addr, socklen);
    SYSCALL_ERROR(code == -1);


    // Read the data and obtain the address of the client.
    // The datagram protocol is connectionless, and it is necessary to master the address information of both parties to enable two-way communication.
    memset(buff, 0, sizeof(buff));
    code = recvfrom(socketfd, buff, sizeof(buff), 0, (struct sockaddr *)&addr, &socklen);
    SYSCALL_ERROR(code == -1);
    printf("client %s message: %s\n", inet_ntoa(addr.sin_addr), buff);

    code = sendto(socketfd, buff, strlen(buff), 0, (struct sockaddr *)&addr, socklen);
    SYSCALL_ERROR(code == -1);

finally:
    if (socketfd) close(socketfd);
    if (clientfd) close(clientfd);
    return EXIT_SUCCESS;
}
