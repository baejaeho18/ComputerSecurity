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
TCP/IP Protocol : Application > Transport > Network > Link > Physics Layers
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
   -> create master key both
<img width="400" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/594f89ff-3c0e-4474-ba0b-bd3c44b594ef"> <br>
   -> create session key both
4) Handshake done <- SSL ChangeCipherSpec Protocol

### SSL Record Protocol
For **Confidentiality**(encrpyt by shared secret key) and **Message Integrity**(generate MAC)
<img width="600" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/c19848d6-b634-4a54-8118-3c907907e2a9"> <br>
MAC = hash(MAC_write_secret, pads, seq_num, etc)
Header : Content Type(handshake/alert/change cipher), versions(3.1 -> 3, 1), compression length

### SSL ChangeChiperSpec Protocol
A single byte message(0x01) to sign the completeness of updating SSL parameters
<img width="500" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/33b97c4e-174d-448a-858a-a4e264f5c278">

### SSL Alert Protocol
To warning or fatal
<img width="500" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/264972fa-0e25-4a3f-b6f9-071a460e37de">

## Email & Set
### Email Review and Secure Email
### Pretty Good Privacy(PGP)
### Secure/Multipurpose Internet Mail Extensions(S/MIME)
~~### Secure Electronic Transaction (SET)~~

# Ch7.User Authentication Mechanisms
### Password based Authentication
### Authentication Token
### Certificate based authentication
### Biometric Authentication
### Kerberos

# Ch9. Network Security
## Introduction of Firewalls
### Types of Firewalls
### Firewall Configurations
### Demilitarized Zone Networks
### Limitations of Firewall

## IPSec Overview
### IPSec Operation Modes
### IPSec Security Protocols
### IPSec Process
### Virtual Private Network
