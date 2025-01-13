#include "ft_malcolm.h"

bool is_equal_ip(const uint8_t *ip_1_in_bytes, const char *ip_2_in_str) {
    char ip_1_in_str[15];
    ip_bytes_to_str(ip_1_in_bytes, ip_1_in_str);
    return ft_strncmp(ip_1_in_str, ip_2_in_str, IP_ADDRESS_LENGTH) == 0;
}

bool is_equal_mac(const uint8_t mac_1_in_bytes[ETH_ALEN], const char *mac_2_in_str) {
    char mac_1_in_str[MAC_ADDRESS_LENGTH];
    mac_bytes_to_str(mac_1_in_bytes, mac_1_in_str);
    return ft_strncmp(mac_1_in_str, mac_2_in_str, MAC_ADDRESS_LENGTH) == 0;
}