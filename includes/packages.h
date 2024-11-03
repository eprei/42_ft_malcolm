/*
** ARP (Address Resolution Protocol) Package
** Implementation based on RFC 826: "An Ethernet Address Resolution Protocol"
** https://tools.ietf.org/html/rfc826
**
** This file contains the structures and definitions needed for
** ARP packet creation and handling.
*/

#ifndef PACKAGES_H
# define PACKAGES_H

# define AR_OP_REQUEST 1
# define AR_OP_REPLY 2
# define ETHERNET 1
#define ETHERTYPE_ARP 0x0806 // EtherType value for ARP protocol As defined in IEEE standards

typedef struct s_ether_packet_header
{
    char *target_mac_address;
    char *source_mac_address;
    char *ether_type; // ETHERTYPE_ARP

} t_ether_packet_header;

typedef struct s_arp_packet
{
    char *ether_type; // Specific type $ADDRESS_RESOLUTION
    char *ar_hrd; // Hardware address space (e.g., ETHERNET, Packet Radio Net.)
    char *ar_pro; // Protocol address space. For Ethernet hardware, this is from the set of type fields ether_typ$<protocol>.
    char *ar_hln; // byte length of each hardware address
    char *ar_pln; // byte length of each protocol address
    char *ar_op;  // opcode (AR_OP_REQUEST | AR_OP_REPLY)
    char *ar_sha; // Hardware address of sender
    char *ar_spa; // Protocol address of sender
    char *ar_tha; // Hardware address of target
    char *ar_tpa; // Protocol address of target
} t_arp_packet;

void make_arp_packet(void); // TODO
void make_ether_packet_header(void); //TODO

#endif //PACKAGES_H

