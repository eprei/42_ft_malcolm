#include "ft_malcolm.h"

int hex_to_int(const char c){
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return -1;
}

void ip_bytes_to_str(const uint8_t ip_bytes[4], char *ip_str)
{
    sprintf(ip_str, "%d.%d.%d.%d", ip_bytes[0], ip_bytes[1], ip_bytes[2], ip_bytes[3]);
}

void mac_bytes_to_str(const uint8_t mac_bytes[ETH_ALEN], char *mac_str)
{
    sprintf(mac_str, "%02x:%02x:%02x:%02x:%02x:%02x",
        mac_bytes[0], mac_bytes[1], mac_bytes[2],
        mac_bytes[3], mac_bytes[4], mac_bytes[5]);
}