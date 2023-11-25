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
SSL *ssl;
SSL_CTX *ctx;
int sock;

void *send_msg(void *arg);
void *recv_msg();
void send_file(const char *arg);

int main(int argc, char *argv[]) 
{
    struct sockaddr_in serv_addr;
    pthread_t send_thread, recv_thread;

    if (argc != 4) 
	{
        printf("Usage : %s <IP> <port> <name>\n", argv[0]);
        exit(1);
    }
    sprintf(name, "[%s]", argv[3]);

    SSL_library_init();
    ctx = SSL_CTX_new(SSLv23_client_method());
    if (ctx == NULL)
        error_handling("SSL_CTX_new() error");

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

    // 쓰레드 생성
    pthread_create(&send_thread, NULL, send_msg, NULL);
    pthread_create(&recv_thread, NULL, recv_msg, NULL);

    // 쓰레드 종료 대기
    pthread_join(send_thread, NULL);
    // pthread_join(recv_thread, NULL);

    // 쓰레드 에러 발생 시 SSL 및 소켓 종료
    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(sock);
    SSL_CTX_free(ctx);
	printf("Good Termination");
    return 0;
}

void *send_msg(void *arg) 
{
    char name_msg[NAME_SIZE + BUF_SIZE];
	char cmd = "file_share:";
    while (1)
	{
        fgets(msg, BUF_SIZE, stdin);
		printf("%s", msg);
		if (strncmp(name_msg, cmd, strlen(cmd)) == 0) 
        {
            // 파일 이름 추출
            char *file_name = name_msg + strlen(cmd);
            // 파일 전송 함수 호출
			printf("%s", file_name);
            send_file(file_name);
        }
        else if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n")) 
		{
			// return NULL;
            close(sock);
            SSL_free(ssl);
            SSL_CTX_free(ctx);
            exit(0);
        }

        sprintf(name_msg, "%s %s", name, msg);

        // TLS로 암호화된 데이터 전송
        if (SSL_write(ssl, name_msg, strlen(name_msg)) <= 0)
            error_handling("SSL_write() error");
    }
    return NULL;
}

void *recv_msg() 
{
    char name_msg[NAME_SIZE + BUF_SIZE];
    while (1) 
	{
        // TLS로 암호화된 데이터 수신
        int str_len = SSL_read(ssl, name_msg, sizeof(name_msg) - 1);
        if (str_len <= 0)
            error_handling("SSL_read() error");

        name_msg[str_len] = 0;
        fputs(name_msg, stdout);
    }
    return NULL;
}

void send_file(const char *file_name) 
{
    FILE *file = fopen(file_name, "rb");
    if (file == NULL) 
    {
        fprintf(stderr, "Error opening file: %s\n", file_name);
        return;
    }
    // 파일 크기 확인
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    // 파일 내용 읽기
    char *file_buffer = (char *)malloc(file_size);
    fread(file_buffer, 1, file_size, file);

    // 파일 이름과 크기를 서버로 전송
    char file_info[BUF_SIZE];
    snprintf(file_info, sizeof(file_info), "file_share:%s(%ld)", file_name, file_size);
    if (SSL_write(ssl, file_info, strlen(file_info)) <= 0)
        error_handling("SSL_write() error");
    // 파일 내용을 서버로 전송
    if (SSL_write(ssl, file_buffer, file_size) <= 0)
        error_handling("SSL_write() error");

    // 메모리와 파일 자원 해제
    free(file_buffer);
    fclose(file);
}


void error_handling(char *msg) 
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    ERR_print_errors_fp(stderr);
    exit(1);
}
