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

int is_target_arp_packet(const char *source_ip, const char *target_ip, const char *target_mac_address,
    const union etherframe frame) {
    return ntohs(frame.field.header.ether_type) == ETH_P_ARP &&
           is_equal_mac(frame.field.header.ether_shost, target_mac_address) &&
           is_equal_ip(frame.field.arp.arp_spa, target_ip) &&
           is_equal_ip(frame.field.arp.arp_tpa, source_ip);
}
