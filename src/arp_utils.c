#include "ft_malcolm.h"

void spoof_arp_mac_addr(uint8_t arp_sha[], const char *mac_str)
{
    int j = 0;

    for (int i = 0; i < 16; i = i + 3) {
        const int high = hex_to_int(mac_str[i]);
        const int low = hex_to_int(mac_str[i + 1]);
        arp_sha[j++] = high << 4 | low;
    }
}

void print_arp_request(const char *target_ip, const char *target_mac_address) {
    printf("An ARP request has been broadcast.\n");
    printf("\tMac address of request: %s\n", target_mac_address);
    printf("\tIP address of request: %s\n", target_ip);
}