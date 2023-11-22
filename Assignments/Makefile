CC = gcc
SERVER = tls_chat_serv.c
CLIENT = tls_chat_clnt.c
SERV_TARGET = serv
CLNT_TARGET = clnt

all: $(SERV_TARGET) $(CLNT_TARGET)

$(SERV_TARGET): $(SERVER)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(CLNT_TARGET): $(CLIENT)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

run: $(SERV_TARGET) $(CLNT_TARGET)
	./$(SERV_TARGET) & ./$(CLNT_TARGET)

clean:
	rm -f $(SERV_TARGET) $(CLNT_TARGET)