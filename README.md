
# ft_malcolm

## Introduction
This project focuses on implementing an Address Resolution Protocol (ARP) spoofing/poisoning method, a basic type of Man-in-the-Middle (MITM) attack. The project is part of a network security course and serves to introduce students to network vulnerabilities.

## Features
- Simulates ARP spoofing on IPv4 networks
- Responds to ARP requests and sends spoofed ARP replies
- Handles network errors and invalid input formats

## Usage
The program requires four command-line arguments:
```
./ft_malcolm <source_ip> <source_mac> <target_ip> <target_mac>
```
Example:
```
sudo ./ft_malcolm 10.12.255.255 ff:bb:ff:ff:ee:ff 10.12.10.22 10:dd:b1:**:**:**
```

### Output:
- Listens for ARP requests and sends spoofed ARP replies.
- Updates the ARP table on the target with the provided spoofed IP and MAC address.

## Compilation
Use the provided Makefile to compile the project:
```
make
```

## Bonus Features (if implemented)
- Decimal notation for IPv4 addresses
- Hostname resolution for IPv4 addresses
- Verbose mode for packet information

## Disclaimer
This project is for educational purposes only.
