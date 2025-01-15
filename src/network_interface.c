#include "ft_malcolm.h"

bool interface_is_in_target_network(struct ifaddrs *ifap, const char *target_ip) {
    const struct sockaddr_in *addr_1 = (struct sockaddr_in *) ifap->ifa_addr;
    const struct sockaddr_in *netmask = (struct sockaddr_in *) ifap->ifa_netmask;
    struct sockaddr_in addr_2;

    if (netmask == NULL) {
        // fprintf(stderr, "netmask in %s is null\n", ifap->ifa_name);
        return false;
    }

    addr_2.sin_family = AF_INET;
    if (inet_pton(AF_INET, target_ip, &addr_2.sin_addr) != 1) {
        // fprintf(stderr,"Error: invalid IP address: %s\n", target_ip);
        return false;
    }

    const in_addr_t network_1 = addr_1->sin_addr.s_addr & netmask->sin_addr.s_addr;
    const in_addr_t network_2 = addr_2.sin_addr.s_addr & netmask->sin_addr.s_addr;

    return network_1 == network_2;
}

bool is_suitable_interface(struct ifaddrs *ifap, const char *target_ip) {
    return ifap->ifa_addr != NULL &&
           ifap->ifa_addr->sa_family == AF_INET &&
           !(ifap->ifa_flags & IFF_LOOPBACK) &&
           ifap->ifa_flags & IFF_UP &&
           interface_is_in_target_network(ifap, target_ip);
}

void find_suitable_interface(char *interface_name, const char *target_ip) {
    struct ifaddrs *ifap_head;

    if (getifaddrs(&ifap_head) == -1) {
        fprintf(stderr, "Error finding network adapter: %s\n", strerror(errno));
    } else {
        for (struct ifaddrs *ifap_current = ifap_head; ifap_current != NULL; ifap_current = ifap_current->ifa_next) {
            if (is_suitable_interface(ifap_current, target_ip)) {
                ft_memcpy(interface_name, ifap_current->ifa_name, ft_strlen(ifap_current->ifa_name) + 1);
                printf("Found suitable interface: %s\n", interface_name);
                break;
            }
        }
    }
    freeifaddrs(ifap_head);
}