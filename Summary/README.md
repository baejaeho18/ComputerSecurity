# Ch5. Public Key Infrastructure(PKI)
## Symmetric Key
pros : Effective when enciphering large message <br>
cons : Need to share secret key : $\frac{n(n-1)}{2}$ <br>
1) Number of Keys
2) How to distribute the keys? <br>
=> Solution : Use a trusted third party <br>
### Symmetric Key Distribuiton
<img width="500" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/9ab13145-640e-4d09-a71b-e164840520b4"> <br>
Multiple KDC(Key-Distribution Center) and each memebers establish a secret key <br>
A temporary session symmetric key is created by KDC using two member's secret key <br>
- Needham-Schroeder Protocol <br>
<img width="600" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/243dc28f-1637-4208-8a33-09c61d6887c2"> <br>
A request to KDC and KDC give what to send to Bob <br>
- Otway-Rees Protocol <br>
<img width="600" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/ae058dd2-24b8-4052-8715-d50446f4bf3f"> <br>
A suggest to B and B request session key to KDC <br>
### Symmetric Key Agreement
Create a session key between themselves without using KDC <br>
=> **Diffle-Hellman Protocol** <br>
<img width="600" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/61f7c517-6d17-4f12-ae49-26fae425cecf"> <br><br>
In response to Man-in-the-Middle attack(creates z) <br>
<img width="300" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/3c7d6d81-a814-4bcc-b46f-72012384c1b4"> <br>
=> Station-to-Station Protocol : Add digital signatures

## Pulic Key
### Public Key Distribution
Just announce the public key is subject to forgery <br>
=> Controlled Trusted Center (with signature) <br>
=> CA(Certification Authority) : "I, the CA, guarantee that 48924579 is A's public key" <br>
<img width="400" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/bbd5d1ac-8de9-4015-8f06-d9d59a373c25">
### Public Key Certificate(PKC)
Digital Certificate binds a user with its public key signed by a CA <br>
X.509 standard : User, Validity, Public key... <br>
<img width="400" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/675e8f95-e140-4d47-97eb-86691e7f2859">
### Public Key Infrastructure (PKI)
<img width="400" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/7fb4acbc-067e-487c-b2e6-4107815aaf8f"> <br>
RA got requests, CA generates certificates, server stores private keys and directory stores certificates <br>
Key generation -> Registration -> Verification -> Certificate creation <br>

OCSP (Online Certificate Status Protocol) : 

# Ch6. Internet Security Protocols
## Internet Security Approach
TCP/IP Protocol : Application > Transport > Network > Link > Physics Layers <br>
<img width="600" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/bf77b896-3549-4525-acab-96abe0dda50f">

## Basic of SSL
SSL(Secure Socket Layer)) is a **Transport layer** security service which encrpyts and also authenticates. It becames TLS(Transport Layer Security)
- Session : client-server like
- Connection : peer-to-peer

Following four SSL Protocols are used
### SSL Handshake Protocol
Allow the server and client to **authenticate** each other <br>
<img width="800" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/2873f947-790a-40b1-aa78-58e5e2ad859c">
1) Establish Securit Capabilities
   - Client Hello (nonce, cipher suite, session_id)
   - Server Hello (nonce, cipher, CA)
2) Client validate CA using CA's public key <br>
   -> open server's public key
3) Client send Pre-master key to Server <br>
   -> create master key both <br>
<img width="400" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/594f89ff-3c0e-4474-ba0b-bd3c44b594ef"> <br>
   -> create session key both
4) Handshake done <- SSL ChangeCipherSpec Protocol
### SSL Record Protocol
For **Confidentiality**(encrpyt by shared secret key) and **Message Integrity**(generate MAC) <br>
<img width="600" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/c19848d6-b634-4a54-8118-3c907907e2a9"> <br>
MAC = hash(MAC_write_secret, pads, seq_num, etc) <br>
Header : Content Type(handshake/alert/change cipher), versions(3.1 -> 3, 1), compression length
### SSL ChangeChiperSpec Protocol
A single byte message(0x01) to inform the completeness of updating SSL parameters <br>
<img width="500" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/33b97c4e-174d-448a-858a-a4e264f5c278">
### SSL Alert Protocol
To warning or fatal <br>
<img width="500" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/264972fa-0e25-4a3f-b6f9-071a460e37de">

## Email ~~& Set~~
 Components
- user agent : mail reader using e-mail access protocol(POP3, IMAP, HTTP)
- mail server(receiver&sender) : mailbox(incoming), message queue(outgoing)
- SMTP(Simple Mail Transfer Protocol) : between mail servers(port 25) <br>
<img width="600" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/7b5d06a5-ed8a-49cd-8d37-4c07a0343c4f"> <br>
### Email Review and Secure Email
Connfidentiality, message Integrity, Authentication <br>
 => Use three Keys : Alice's private key, Bob's public key, new symmetric key <br>
<img width="600" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/8b5e73a0-d93c-4fe3-a8b8-8efb56f90f1a"> <br>
### Pretty Good Privacy(PGP)
<img width="600" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/e44e4e40-f658-4931-a78b-3406043ae309"> <br>
1) Create signature(using sender's private key) and attach to message
2) Compression
3) Encrpyt both message and signature (using session key)
4) Attach RSA/ElGamal encrpyted session key (using receiver's public key) <br>
<img width="600" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/62bd7e0e-adde-43af-8108-ca9fb634cb7c">

### Secure/Multipurpose Internet Mail Extensions(S/MIME)
S/MIME(Secure/Multipurpose Internet Mail Extensions) provide support for varying content types and security enhancements <br>
Functions:
- Enveloped data : encrpyt message with receiver's public key
- Signed data : encrpyted message and its sign
- Clear-signed data : clear message and its sign
- Signed & enveloped data : message and its sign both encrypted

~~### Secure Electronic Transaction (SET)~~

# Ch7.User Authentication Mechanisms
Authentication : "The process by which the identity of someone or something gets established"
- Verification : "Is the claimant the person who he or she claims to be?" : one-to-one
- Identfification : "Is the claimant an erolled user and who is he/she?" : one-to-many
### Password based Authentication
Possilbe attack : Replay attack, Password-Guessing attack, ... <br>
Protecting PW files : Hashing and Salting <br>
<img width="688" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/fc78e01d-bfc0-42d6-94c5-719310e307cf"> <br>
Clear PW -> Message Digests of PW -> One-Time PW
   - Lamport one-time password : $h^{n}(x)=h(h^{n-1}(x))$

### Authentication Token
Rules:
   - Token and server are synchronized initially
   - Token generates fresh passwords periodically
**Zero-Knkowledge Proof** : The claimant proves to the verifier that he knows a secret wihtout revealing it
- Fiat-Shamir Protocol
### Certificate based authentication
Based on PKI, CA proves authentication
### Biometric Authentication
<img width="400" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/322e695e-0387-4f36-97a4-d516468cdcda"> <br>

~~### Kerberos~~

# Ch9. Network Security
## Introduction of Firewalls
Firewall is a special type of network router. It controls transmission between internal and external networks.
### Types of Firewalls
<img width="900" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/75ec944c-ceef-4333-b8e7-efcc83e47699"> <br>
- Packet Filters(screen router) : Block packets based on information in the header(ip-network, port-transport, ...)
   - simplest, fastest
   - stateless/stateful filtering
- Application Gateway(proxy server) : Block packets based on the contents of messages
   - additional overhead needed
### Firewall Configurations
<img width="500" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/a7b482d6-c460-4c15-8abd-7bff18b59177"> 

### Demilitarized Zone Networks
DMZ is simply a network segment that is located between the protected and the unprotected networks
### Limitations of Firewall

## IPSec Overview
IPSec is a general IP security mechanisms. It provides authentication, confidentiality, key management <br>
<img width="400" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/ba71fa9d-379b-4e11-8063-c0640bfb8190"><br>
### IPSec Operation Modes
- Trnasport Mode : between trasnport layer and network layer <br>
<img width="600" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/5a94f426-798d-4fe3-9b94-f3d624b327b9"> <br>
- Tunnel Mode : between two network layter <br>
<img width="600" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/91ed1b14-1200-4628-a146-75e3595f7d8d"> 
  
### IPSec Security Protocols
- AH(Authentication Header) : provide **authentication and data integrity**
<img width="600" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/867c9e7d-8814-48d5-8dc0-98459498056c"> <br>
- ESP(Encapsulationg Security Payload) : provide authentication and data integrity **and privacy(encrpytion)**
<img width="600" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/ab7e3b68-ff97-48ea-839e-74012a58202b"> <br>

### IPSec Process
SA(Security Association), SAD : how to do it <br>
SP(Seucrity Policy), SPD : what to do it(drop, bypass, apply) <br>
<img width="919" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/9b0be814-8351-4bd8-9942-750fc6115804">

### Virtual Private Network
<img width="639" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/995ec77a-120a-4f6a-a16a-2d7c28437edc"> <br>
Based on IP tunneling, hide original IP address






