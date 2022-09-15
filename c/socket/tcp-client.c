#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SYSCALL_ERROR(expression) \
    if (expression) { \
        printf("%s %d: %s\n", __FILE_NAME__, __LINE__, strerror(errno)); \
        goto finally; \
    }

int main() {
    int ssocketfd = -1;
    struct sockaddr_in saddr;
    struct hostent *host;
    int code;
    socklen_t saddr_len = sizeof(saddr);
    const char *message = "Hello World";
    char buff[BUFSIZ];
    const int tcp_retries = 3;
    struct timeval timeout = {10, 0};

    // Quey DNS.
    host = gethostbyname("localhost");
    if (!host) {
        printf("%s %d: %s\n", __FILE_NAME__, __LINE__, hstrerror(h_errno));
        goto finally;
    }
    printf("ip: %s\n", inet_ntoa(*((struct in_addr *) host->h_addr)));
    // Set the IP address and address type.
    saddr.sin_family = host->h_addrtype;
    memcpy(&saddr.sin_addr.s_addr, host->h_addr, host->h_length);
    saddr.sin_port = htons(8080);

    // Create a socket using the TCP protocol.
    ssocketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    SYSCALL_ERROR(ssocketfd == -1);
    // Set the number of TCP handshake retries.
    code = setsockopt(ssocketfd, IPPROTO_TCP, TCP_SYNCNT, &tcp_retries, sizeof(tcp_retries));
    SYSCALL_ERROR(code == -1);
    // Set the socket read and write timeout.
    code = setsockopt(ssocketfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    SYSCALL_ERROR(code == -1);
    code = setsockopt(ssocketfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
    SYSCALL_ERROR(code == -1);
    code = connect(ssocketfd, (struct sockaddr *)&saddr, saddr_len);
    SYSCALL_ERROR(code == -1);
    printf("connected server\n");

    code = send(ssocketfd, message, strlen(message), 0);
    SYSCALL_ERROR(code == -1);
    memset(buff, 0, sizeof(message));
    code = recv(ssocketfd, buff, BUFSIZ, 0);
    SYSCALL_ERROR(code == -1);
    printf("server message: ");
    fwrite(buff, code, 1, stdout);
    printf("\n");

finally:
    if (ssocketfd != -1) close(ssocketfd);
    return 0;
}
