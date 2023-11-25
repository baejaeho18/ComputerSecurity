1. 구현한 프로그램의 사용 방법(서버/클라이언트 모두)


2. 사용 라이브러리 버전 등 프로그램 컴파일과 실행에 필요한 모든 정보

21700331@ubuntu:~/ComputerSecurity/Assignments$ openssl req -x509 -newkey rsa:4096 -keyout server.key -out server.crt -days 365
Generating a RSA private key
......................................................++++
....++++
writing new private key to 'server.key'
Enter PEM pass phrase:
Verifying - Enter PEM pass phrase: comsec
-----
You are about to be asked to enter information that will be incorporated
into your certificate request.
What you are about to enter is what is called a Distinguished Name or a DN.
There are quite a few fields but you can leave some blank
For some fields there will be a default value,
If you enter '.', the field will be left blank.
-----
Country Name (2 letter code) [AU]:KR
State or Province Name (full name) [Some-State]:
Locality Name (eg, city) []:Pohang
Organization Name (eg, company) [Internet Widgits Pty Ltd]:HGU
Organizational Unit Name (eg, section) []:comsec
Common Name (e.g. server FQDN or YOUR name) []:203.252.112.24
Email Address []:

# 서버 및 클라이언트 컴파일


# 서버 실행
21700331@ubuntu:~/ComputerSecurity/Assignments$ make server
./serv 9690
Enter PEM pass phrase: comsec


# client 실행


