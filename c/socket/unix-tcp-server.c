#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "test.sock"

#define SYSCALL_ERROR(expression) \
    if (expression) { \
        printf("%s %d: %s\n", __FILE_NAME__, __LINE__, strerror(errno)); \
        goto finally; \
    }

int main() {
    int socketfd = -1, clientfd = -1;
    struct sockaddr_un addr;
    int code = 0;
    socklen_t socketlen = sizeof(addr);
    char buff[BUFSIZ];

    /*
     The third parameter of the socket() function is used to the protocol field of the IP packet header to be sent or received,
     which has no meaning for unix domain sockets.
     */
    socketfd = socket(AF_UNIX, SOCK_STREAM, 0);
    SYSCALL_ERROR(socketfd == -1);
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_PATH);
    code = bind(socketfd, (struct sockaddr *)&addr, sizeof(addr));
    SYSCALL_ERROR(code == -1);
    // Sets the listening queue size of the socket.
    code = listen(socketfd, 50);
    SYSCALL_ERROR(code == -1);

    clientfd = accept(socketfd, (struct sockaddr *)&addr, &socketlen);
    SYSCALL_ERROR(clientfd == -1);
    printf("client socket file path: %s\n", addr.sun_path);

    code = recv(clientfd, buff, sizeof(buff), 0);
    SYSCALL_ERROR(code == -1);
    printf("client message: ");
    fwrite(buff, code, 1, stdout);
    printf("\n");
    code = send(clientfd, buff, code, 0);
    SYSCALL_ERROR(code == -1);

finally:
    if (socketfd != -1) close(socketfd);
    if (clientfd != -1) close(clientfd);
    unlink(SOCKET_PATH);
    return EXIT_SUCCESS;
}
