#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H

/* libraries */
# include <stdbool.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <net/if.h>
# include <sys/socket.h>
# include <ifaddrs.h>
# include <netpacket/packet.h>
# include <net/ethernet.h>
# include <netinet/if_ether.h>
# include <signal.h>
# include <errno.h>

/* macros */
# define BINARY_NAME "./ft_malcolm"
# define EXPECTED_NUMBER_OF_ARGUMENTS 5
# define IP_ADDRESS_LENGTH 15
# define MAC_ADDRESS_LENGTH 17
# define FRAME_LEN sizeof(struct ether_header) + sizeof(struct ether_arp)
# define IPV4_ADDR_LEN sizeof(struct in_addr)

/* structures */
union etherframe
{
    struct
    {
        struct ether_header header;
        struct ether_arp    arp;
    } field;
    unsigned char full_frame[FRAME_LEN];
};

/* colours */
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

/* messages to print */
# define USAGE_MSG "USAGE: sudo " BINARY_NAME " <source ip> <source mac address> <target ip> <target mac address>\n"
# define USAGE_EXAMPLE "USAGE_EXAMPLE: sudo " BINARY_NAME " \"192.168.56.110\" \"42:42:42:42:42:42\" \"192.168.56.112\" \"08:00:27:ec:a4:df\"\n"
# define INVALID_IP_MSG RED "Unknown host or invalid IP address: %s\n" RESET
# define INVALID_MAC_MSG RED "Invalid MAC address: %s\n" RESET

/* valid_arguments.c */
bool valid_arguments(int argc, char **argv);

/* convert.c */
int hex_to_int(char c);
void ip_bytes_to_str(const uint8_t ip_bytes[4], char *ip_str);
void mac_bytes_to_str(const uint8_t mac_bytes[ETH_ALEN], char *mac_str);

/* compare.c */
bool is_equal_ip(const uint8_t *ip_1_in_bytes, const char *ip_2_in_str);
bool is_equal_mac(const uint8_t mac_1_in_bytes[ETH_ALEN], const char *mac_2_in_str);

/* arp_utils.c */
void spoof_arp_mac_addr(uint8_t arp_sha[], const char *mac_str);
void print_arp_request(const char *target_ip, const char *target_mac_address);
int is_target_arp_packet(const char *source_ip, const char *target_ip, const char *target_mac_address, union etherframe frame);

/* libft.c */
void *ft_memcpy(void *dst, const void *src, size_t n);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_tolower(int c);
size_t	ft_strlen(const char *s);

/* network_interface.c */
bool interface_is_in_target_network(struct ifaddrs *ifap, const char *target_ip);
bool is_suitable_interface(struct ifaddrs *ifap, const char *target_ip);
void find_suitable_interface(char *interface_name, const char *target_ip);

#endif
