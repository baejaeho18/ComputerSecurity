#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define BUF_SIZE 100
#define NAME_SIZE 20
#define MAX_CLIENTS 3
#define CERT_FILE "server.crt"
#define KEY_FILE "server.key"

typedef struct {
    int clnt_sock;
    SSL *ssl;
} ClientInfo;

ClientInfo clients[MAX_CLIENTS];
pthread_mutex_t mutex;
int client_cnt = 0;

void *handle_client(void *arg);
void send_to_all(char *msg, int sender_index);
void send_file_to_all(const char *file_msg, int sender_self_index);
void error_handling(char *msg);

int main(int argc, char *argv[]) 
{
    SSL_CTX *ctx;
    SSL *ssl;
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;

    if (argc != 2) 
	{
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

	// SSL 라이브러리 초기화
    SSL_library_init();
	// SSL 컨텍스트 생성
    ctx = SSL_CTX_new(SSLv23_server_method());
    if (ctx == NULL)
        error_handling("SSL_CTX_new() error");

	// 인증서와 개인 키 로딩
    if (SSL_CTX_use_certificate_file(ctx, CERT_FILE, SSL_FILETYPE_PEM) <= 0 ||
        SSL_CTX_use_PrivateKey_file(ctx, KEY_FILE, SSL_FILETYPE_PEM) <= 0)
    {
        error_handling("SSL_CTX_use_certificate_file() or SSL_CTX_use_PrivateKey_file() error");
    }

	// 서버 소켓 생성 및 초기화
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");

    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    clnt_addr_size = sizeof(clnt_addr);

    while (1) 
	{
        int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        if (clnt_sock == -1) 
		{
            perror("accept() error");
            continue;
        }

        SSL *ssl = SSL_new(ctx);
        SSL_set_fd(ssl, clnt_sock);

        if (SSL_accept(ssl) == -1) 
		{
            close(clnt_sock);
            SSL_free(ssl);
            continue;
        }

        // 클라이언트 정보 구조체를 생성하고 스레드를 시작
        ClientInfo *client_info = (ClientInfo *)malloc(sizeof(ClientInfo));
        client_info->clnt_sock = clnt_sock;
        client_info->ssl = ssl;

        // 배열에 클라이언트 정보를 안전하게 추가
        pthread_mutex_lock(&mutex);
		if (client_cnt < MAX_CLIENTS)
			clients[client_cnt++] = *client_info;
        pthread_mutex_unlock(&mutex);

        pthread_t client_thread;
        pthread_create(&client_thread, NULL, handle_client, (void *)client_info);
        pthread_detach(client_thread);  // 스레드가 종료 시 자동으로 해제
    }

    // SSL 및 서버 소켓 종료
    close(serv_sock);
    SSL_CTX_free(ctx);

    return 0;
}

void *handle_client(void *arg) 
{
    ClientInfo *client_info = (ClientInfo *)arg;
    int clnt_sock = client_info->clnt_sock;
    SSL *ssl = client_info->ssl;
    char client_msg[BUF_SIZE];
	const char *cmd = "file_share:";

	int str_len = 0, i;
	while ((str_len = SSL_read(ssl, client_msg, sizeof(client_msg) - 1)) != 0)
	{
		if (strncmp(client_msg, cmd, 11) == 0)
			send_file_to_all(client_msg, clnt_sock);
		else
			send_to_all(client_msg, clnt_sock);
	}

    // 해당 클라이언트의 정보를 초기화하고 소켓 및 SSL 자원을 해제
    pthread_mutex_lock(&mutex);
	for (i = 0; i < client_cnt; i++)   // remove disconnected client
	{
		if (clnt_sock == clients[i].clnt_sock)
		{
			while (i < client_cnt - 1)
			{
				clients[i] = clients[i + 1];
				i++;
			}
			break;
		}
	}
	client_cnt--;
    pthread_mutex_unlock(&mutex);

    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(clnt_sock);
    // 클라이언트 정보를 담은 구조체를 해제
    free(client_info);  

    return NULL;
}

void send_to_all(char *message, int sender_self_index) 
{
	message[strlen(message)] = '\0';
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < client_cnt; ++i)
        if (clients[i].clnt_sock != 0 && clients[i].clnt_sock != sender_self_index)
            SSL_write(clients[i].ssl, message, strlen(message));
    pthread_mutex_unlock(&mutex);
}

void send_file_to_all(const char *file_msg, int sender_self_index) 
{
    // 파일 정보에서 파일 이름과 크기 추출
    char file_name[NAME_SIZE];
    long file_size;
    sscanf(file_msg + 11, "%s(%ld)", file_name, &file_size);

	printf("%s", file_name);
    // 파일 데이터 수신
    char file_buffer[file_size];
	for (int i = 0; i < client_cnt; ++i)
        if (clients[i].clnt_sock == sender_self_index)
            if (SSL_read(clients[i].ssl, file_buffer, file_size) <= 0)
        		error_handling("SSL_read() error");

    // 파일 저장 (예: 현재 디렉터리에 저장)
    FILE *file = fopen(file_name, "wb");
    if (file == NULL) 
    {
        fprintf(stderr, "Error opening file for writing: %s\n", file_name);
        return;
    }
    fwrite(file_buffer, 1, file_size, file);
    fclose(file);

    // 파일 수신 완료 메시지 또는 다른 클라이언트들에게 파일 전송 메시지 전송 등의 추가 로직 수행
    printf("File received");

    // 모든 클라이언트에게 파일 전송 메시지 전송
    char broadcast_msg[BUF_SIZE];
    snprintf(broadcast_msg, sizeof(broadcast_msg), "file_shared:%s", file_name);
    send_to_all(broadcast_msg, sender_self_index);
}

void error_handling(char *msg) 
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    ERR_print_errors_fp(stderr);
    exit(1);
}
