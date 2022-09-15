#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SYSCALL_ERROR(expression) \
    if (expression) { \
        printf("%s %d: %s\n", __FILE_NAME__, __LINE__, strerror(errno)); \
        goto finally; \
    }

int main() {
    int sockfd = -1, clientfd = -1;
    struct sockaddr_in saddr;
    int code;
    int queueSize = 10;
    struct sockaddr_in caddr;
    socklen_t caddr_len = sizeof(caddr);
    char buff[BUFSIZ];
    const int tcp_retries = 3;
    struct timeval timeout = {10, 0};

    // Create a socket using TCP.
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    SYSCALL_ERROR(sockfd == -1);
    // Set the number of TCP handshake retries.
    code = setsockopt(sockfd, IPPROTO_TCP, TCP_SYNCNT, &tcp_retries, sizeof(tcp_retries));
    SYSCALL_ERROR(code == -1);
    // Set the socket read and write timeout.
    code = setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    SYSCALL_ERROR(code == -1);
    code = setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
    SYSCALL_ERROR(code);

    saddr.sin_port = htons(8080);
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // bind address.
    code = bind(sockfd, (struct sockaddr *)(&saddr), sizeof(saddr));
    SYSCALL_ERROR(code == -1);
    // Listen on the port and set the size of the connection establishment request queue.
    code = listen(sockfd, 10);
    SYSCALL_ERROR(code == -1);


    // Waiting for client to connect.
    clientfd = accept(sockfd, (struct sockaddr *)(&caddr), &caddr_len);
    printf("Connection established successfully! client ip: %s\n", inet_ntoa(caddr.sin_addr));

    memset(buff, 0, sizeof(buff));
    code = recv(clientfd, buff, sizeof(buff), 0);
    SYSCALL_ERROR(code < 0);
    printf("client message: ");
    fwrite(buff, code, 1, stdout);
    printf("\n");
    code = send(clientfd, buff, code, 0);
    SYSCALL_ERROR(code < 0);

finally:
    if (sockfd != -1) close(sockfd);
    if (clientfd != -1) close(clientfd);
    return EXIT_SUCCESS;
}
