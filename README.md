# ft_malcolm

A C program that implements Address Resolution Protocol (ARP) spoofing/poisoning, demonstrating one of the most basic Man-in-the-Middle (MITM) attacks. This project explores network security concepts by exploiting vulnerabilities in the ARP protocol implementation.

## Project Status

**🚧 Under Active Development**

Current Status:
- ✅ Project structure and build system
- ✅ Input validation for IP and MAC addresses
- ⏳ Signal handling (Pending)
- 🚧 ARP packet creation (In Progress)
- ⏳ Network packet handling (Pending)
- ⏳ ARP spoofing implementation (Pending)

## About The Project

ft_malcolm is an educational project focused on understanding network security, specifically the Address Resolution Protocol (ARP) and its vulnerabilities. The program allows users to perform ARP spoofing by intercepting and modifying ARP requests in a controlled environment.

### Learning Objectives

- Understanding the Address Resolution Protocol (ARP) and its role in network communications
- Learning about Man-in-the-Middle (MITM) attacks and their implications
- Exploring network security vulnerabilities at the OSI Layer 2
- Implementing raw socket programming in C
- Handling network packets and protocol structures
- Working with IPv4 addressing and MAC addresses

## Prerequisites

- Linux environment (kernel > 3.14)
- GCC compiler
- Make utility

> **Note**: This repository includes IntelliJ IDEA configuration files (`.idea` directory) for maintaining consistent 
> development environments across different workspaces. If you're not using IntelliJ IDEA, you can safely ignore the 
> `.idea` directory.

## Installation

1. Clone the repository

2. Compile the program
```bash
make
```

## Usage

The program requires root privileges and takes four mandatory arguments:

```bash
sudo ./ft_malcolm <source_ip> <source_mac> <target_ip> <target_mac>
```

### Arguments

- `source_ip`: Source IP address to spoof
- `source_mac`: Source MAC address to spoof
- `target_ip`: Target IP address
- `target_mac`: Target MAC address

### Example

```bash
sudo ./ft_malcolm 10.12.255.255 ff:bb:ff:ff:ee:ff 10.12.10.22 10:dd:b1:00:00:00
```

### Program Operation

1. The program waits for an ARP request from the target
2. When detected, it sends a single ARP reply with the spoofed information
3. The target's ARP table is updated with the spoofed association
4. The program exits after successful spoofing

## Features

### Mandatory
- IPv4 address handling
- MAC address validation
- Graceful exit with Ctrl+C
- Error handling for invalid inputs
- Single ARP reply spoofing

## Technical Details

The following system calls and functions can be used in this project:
- Network operations: `sendto`, `recvfrom`, `socket`, `setsockopt`
- Address handling: `inet_pton`, `inet_ntop`, `if_nametoindex`
- System utilities: `getuid`, `close`, `sigaction`, `signal`
- Name resolution: `gethostbyname`, `getaddrinfo`, `freeaddrinfo`
- Interface handling: `getifaddrs`, `freeifaddrs`

## Security Notice

⚠️ **Important**: This tool is for educational purposes only. Only use it in controlled environments with systems you own or have explicit permission to test. Unauthorized ARP spoofing may be illegal and can cause network disruptions.
