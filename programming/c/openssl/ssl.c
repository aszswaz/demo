#include <stdio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define HOST "www.example.com"
#define PORT 443

#define SYSCALL_ERROR(expression) \
    if (expression) { \
        printf("%s %d: %s\n", __FILE_NAME__, __LINE__, strerror(errno)); \
        goto finally; \
    }

#define OPENSSL_ERROR(expression) \
    if (expression) { \
        ERR_print_errors_fp(stdout); \
        goto finally; \
    }

#define OPENSSL_IO_ERROR(expression) \
    if (expression) { \
        SSL_get_error(ssl, code); \
        ERR_print_errors_fp(stdout); \
        goto finally; \
    }

typedef struct hostent hostent;
typedef struct in_addr in_addr;
typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

int main() {
    const SSL_METHOD *sslMethod;
    SSL_CTX *sslCtx;
    hostent *host;
    int sock;
    sockaddr_in sock_address;
    int code;
    char buff[BUFSIZ];
    const char *head;
    int len;
    X509 *server_cert;

    SSL_library_init();
    ERR_load_crypto_strings();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    sslMethod = SSLv23_client_method();
    sslCtx = SSL_CTX_new(sslMethod);
    OPENSSL_ERROR(!sslCtx);

    host = gethostbyname(HOST);
    if (!host) {
        printf("%s %d: %s\n", __FILE_NAME__, __LINE__, hstrerror(h_errno));
        goto finally;
    }
    printf("host: %s, ipv4: %s\n", HOST, inet_ntoa(*((struct in_addr *)host->h_addr)));
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    SYSCALL_ERROR(sock == -1);
    sock_address.sin_family = host->h_addrtype;
    sock_address.sin_port = htons(PORT);
    memcpy(&sock_address.sin_addr.s_addr, host->h_addr, host->h_length);
    code = connect(sock, (sockaddr *) &sock_address, sizeof(sockaddr));
    SYSCALL_ERROR(code == -1)

    SSL *ssl = SSL_new(sslCtx);
    OPENSSL_ERROR(!ssl)
    /*
     Set the SNI field. This field is used for server domain name verification during handshake, and it is not encrypted.
     It is currently used by the government to intercept the access of websites without records.
    */
    code = SSL_set_tlsext_host_name(ssl, HOST);
    OPENSSL_ERROR(code != 1);
    // Bind socket.
    code = SSL_set_fd(ssl, sock);
    OPENSSL_ERROR(code != 1);
    // Establish an SSL connection.
    code = SSL_connect(ssl);
    OPENSSL_IO_ERROR(code != 1);
    // The SSL encryption standard to use after negotiating with the server.
    printf("cipher: %s\n", SSL_get_cipher(ssl));
    printf("cipher version: %s\n", SSL_get_cipher_version(ssl));

    // Print the server's certificate.
    server_cert = SSL_get_peer_certificate(ssl);
    OPENSSL_ERROR(!server_cert);
    printf("subject: %s\n", X509_NAME_oneline(X509_get_subject_name(server_cert), 0, 0));
    printf("issuer: %s\n\n", X509_NAME_oneline(X509_get_issuer_name(server_cert), 0, 0));
    X509_free(server_cert);

    head = "GET / HTTP/1.1\r\n"
           "Host: www.example.com\r\n"
           "Connection: keep-alive\r\n"
           "Accept: */*\r\n"
           "User-Agent: openssl-demo\r\n"
           "\r\n";
    code = SSL_write(ssl, head, (int) strlen(head));
    OPENSSL_IO_ERROR(code < 0);

    // The page for www.example.com only needs to be read twice.
    for (int i = 0; i < 2; i++) {
        memset(buff, 0, sizeof(buff));
        len = SSL_read(ssl, buff, sizeof(buff));
        OPENSSL_IO_ERROR(len < 0);
        fwrite(buff, len, 1, stdout);
    }

finally:
    if (ssl) {
        SSL_shutdown(ssl);
        SSL_free(ssl);
    }
    if (sock != -1) close(sock);
    if (sslCtx) SSL_CTX_free(sslCtx);
    return 0;
}
