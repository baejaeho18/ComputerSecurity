# CH5. Public Key Infrastructure(PKI)
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
- Needham-Schroeder Protocol
<img width="600" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/243dc28f-1637-4208-8a33-09c61d6887c2"> <br>
A request to KDC and KDC give what to end to Bob

- Otway-Rees Protocol
<img width="600" alt="image" src="https://github.com/baejaeho18/ComputerSecurity/assets/37645490/ae058dd2-24b8-4052-8715-d50446f4bf3f"> <br>
A suggest to B and B request session key to KDC

### Symmetric Key Agreement

## Pulic Key
### Public Key Distribution
### Public Key Certificate(PKC)
### Public Key Infrastructure (PKI)

# CH6. Internet Security Protocols
## Internet Security Approach
## Basic of SSL
### SSL Handshake Protocol
### SSL Record Protocol
### SSL Change Chiper Spec Protocol and Alert Protocol
## Email & Set
### Email Review and Secure Email
### Pretty Good Privacy(PGP)
### Secure/Multipurpose Internet Mail Extensions(S/MIME)
### Secure Electronic Transaction (SET)

# CH7.User Authentication Mechanisms
### Password based Authentication
### Authentication Token
### Certificate based authentication
### Biometric Authentication
### Kerberos

# CH9. Network Security
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
