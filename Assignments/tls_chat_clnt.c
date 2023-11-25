#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define BUF_SIZE 100
#define NAME_SIZE 20
#define FILE_NAME_SIZE 25

void error_handling(char *msg);

char name[NAME_SIZE] = "[DEFAULT]";
char msg[BUF_SIZE];

int main(int argc, char *argv[]) {
    SSL_CTX *ctx;
    SSL *ssl;
    int sock;
    struct sockaddr_in serv_addr;

    if (argc != 4) {
        printf("Usage : %s <IP> <port> <name>\n", argv[0]);
        exit(1);
    }

    SSL_library_init();
    ctx = SSL_CTX_new(SSLv23_client_method());
    if (ctx == NULL)
        error_handling("SSL_CTX_new() error");

    sprintf(name, "[%s]", argv[3]);

    sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error");

    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);
    if (SSL_connect(ssl) == -1)
        error_handling("SSL_connect() error");

    char name_msg[NAME_SIZE + BUF_SIZE];

    // TLS로 암호화된 통신 시작
    while (1) {
        fgets(msg, BUF_SIZE, stdin);
        if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n")) {
            close(sock);
            SSL_free(ssl);
            SSL_CTX_free(ctx);
            exit(0);
        }

        sprintf(name_msg, "%s %s", name, msg);

        // TLS로 암호화된 데이터 전송
        if (SSL_write(ssl, name_msg, strlen(name_msg)) <= 0) {
            error_handling("SSL_write() error");
        }

        // TLS로 암호화된 데이터 수신
        int str_len = SSL_read(ssl, name_msg, sizeof(name_msg) - 1);
        if (str_len <= 0) {
            error_handling("SSL_read() error");
        }

        name_msg[str_len] = 0;
        fputs(name_msg, stdout);
    }

    close(sock);
    SSL_free(ssl);
    SSL_CTX_free(ctx);

    return 0;
}

void error_handling(char *msg) {
    fputs(msg, stderr);
    fputc('\n', stderr);
    ERR_print_errors_fp(stderr);
    exit(1);
}
