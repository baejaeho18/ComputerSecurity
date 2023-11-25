1. 구현한 프로그램의 사용 방법(서버/클라이언트 모두)
# 초기화
make clean 
# tls_chat_clnt.c tls_chat_serv.c 컴파일
make
# tls_serv.c -> serv 실행
make server
./serv {Your_Port}
# tls_clnt.c -> clnt를 정해진 옵션/임의의 옵션으로 실행
make Alice
make Bob
make Carol
make Dave
make Erin 
make Frank
./clnt {Your_IP} {Your_Port} {Your_Name}

# 채팅 : 채팅을 보낸 당사자를 제외한 모두에게 "[Sender_Name] Send_msg"의 형식으로 전송됨
# 파일 : "file_share:{File_Name}"을 명령어로 인식함. 이를 서버에서 받아 저장 후, 각 client들에게 전송함. 서버가 저장을 마치면 "Recieved"를 출력하고, client가 저장을 시작하면 "file_shared:{File_Name}"을 출력함.
# 종료 : "q" 혹은 "Q"를 입력하면 client는 종료됨.

# 제약 조건
일반 채팅 메시지 길이는 100으로 제한됨
전송할 파일 이름 길이는 25로 제한됨
등록할 수 있는 이름 길이는 20으로 제한됨
동시에 접속할 수 있는 client 수는 10으로 제한됨

2. 사용 라이브러리 버전 등 프로그램 컴파일과 실행에 필요한 모든 정보

# 서버 및 클라이언트 컴파일
1700331@ubuntu:~/ComputerSecurity/Assignments$ make
gcc -Wall -Wextra -o serv tls_chat_serv.c -lpthread -lssl -lcrypto
gcc -Wall -Wextra -o clnt tls_chat_clnt.c -lpthread -lssl -lcrypto

# 서버 실행
21700331@ubuntu:~/ComputerSecurity/Assignments$ make server
./serv 9690
Enter PEM pass phrase: comsec

# client 실행
21700331@ubuntu:~/ComputerSecurity/Assignments$ make Alice
./clnt 203.252.112.24 9690 Alice


