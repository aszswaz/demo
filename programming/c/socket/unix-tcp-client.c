#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "test.sock"

#define SYSCALL_ERROR(expression) \
    if (expression) { \
        printf("%s %d: %s\n", __FILE_NAME__, __LINE__, strerror(errno)); \
        goto finally; \
    }

int main() {
    int sockfd;
    struct sockaddr_un addr;
    int code;
    const char *message = "Hello World";
    char buff[BUFSIZ];

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    SYSCALL_ERROR(sockfd == -1);
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_PATH);
    code = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    SYSCALL_ERROR(code == -1);

    code = send(sockfd, message, strlen(message), 0);
    SYSCALL_ERROR(code == -1);
    code = recv(sockfd, buff, sizeof(buff), 0);
    SYSCALL_ERROR(code == -1);
    printf("server message: ");
    fwrite(buff, code, 1, stdout);
    printf("\n");
finally:
    if (sockfd != -1) close(sockfd);
    return EXIT_SUCCESS;
}
