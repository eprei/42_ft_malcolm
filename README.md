# ft_malcolm

A C program that implements Address Resolution Protocol (ARP) spoofing/poisoning, demonstrating one of the most basic
Man-in-the-Middle (MITM) attacks. This project explores network security concepts by exploiting vulnerabilities in the
ARP protocol implementation.

## Project Status

**✅ Project Completed**

Features Implemented:
- ✅ Project structure and build system
- ✅ Input validation for IP and MAC addresses
- ✅ ARP packet creation and handling
- ✅ Network packet handling
- ✅ ARP spoofing implementation
- ✅ Automatic network interface detection

## About The Project

ft_malcolm is an educational project focused on understanding network security, specifically the Address Resolution
Protocol (ARP) and its vulnerabilities. The program allows users to perform ARP spoofing by intercepting and modifying
ARP requests in a controlled environment.

### Learning Objectives

- Understanding the Address Resolution Protocol (ARP) and its role in network communications
- Learning about Man-in-the-Middle (MITM) attacks and their implications
- Exploring network security vulnerabilities at the OSI Layer 2
- Implementing raw socket programming in C
- Handling network packets and protocol structures
- Working with IPv4 addressing and MAC addresses
- Automatic network interface detection and configuration

## Prerequisites

- Linux environment (kernel > 3.14)
- GCC compiler
- Make utility
- Root privileges for running the program

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
sudo ./ft_malcolm "192.168.56.110" "42:42:42:42:42:42" "192.168.56.112" "08:00:27:ec:a4:df"
```

### Program Operation

1. The program automatically detects and selects a suitable network interface that:
    - Is up and running
    - Is not a loopback interface
    - Is in the same network as the target IP
2. Waits for an ARP request from the target
3. When detected, it sends a single ARP reply with the spoofed information
4. The target's ARP table is updated with the spoofed association
5. The program exits after successful spoofing

## Features

### Implemented Features
- IPv4 address handling and validation
- MAC address validation and conversion
- Error handling for invalid inputs
- Single ARP reply spoofing
- Raw socket packet handling
- ARP packet manipulation
- Automatic network interface detection and configuration

## Testing

The project includes a test suite that can be run using:
```bash
make test
```

The test suite checks:
- Input validation for IP and MAC addresses
- Argument handling
- Error cases
- Valid execution scenarios

## Development Environment

The project includes a Vagrant configuration that sets up three virtual machines:
- Attacker machine (with GUI and development tools)
- Target machine
- Source machine

This allows for testing the ARP spoofing in a controlled environment.

## Technical Details

The project uses the following system calls and functions:
- Network operations: `sendto`, `recvfrom`, `socket`
- Address handling: `inet_pton`, `inet_ntop`, `if_nametoindex`
- System utilities: `close`
- Memory operations: Custom implementation of `memcpy`
- Network interface detection: `getifaddrs`, `freeifaddrs`

## Security Notice

⚠️ **Important**: This tool is for educational purposes only. Only use it in controlled environments with systems you
own or have explicit permission to test. Unauthorized ARP spoofing may be illegal and can cause network disruptions.
