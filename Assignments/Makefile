CC = gcc
SERVER = tls_chat_serv.c
CLIENT = tls_chat_clnt.c
SERV_TARGET = serv
CLNT_TARGET = clnt

all: $(SERV_TARGET) $(CLNT_TARGET)

$(SERV_TARGET): $(SERVER)
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

$(CLNT_TARGET): $(CLIENT)
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

run: $(SERV_TARGET) $(CLNT_TARGET)
	./$(CLNT_TARGET) 9690 & ./$(SERV_TARGET) 9690

clean:
	rm -f $(SERV_TARGET) $(CLNT_TARGET)