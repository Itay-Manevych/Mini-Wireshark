#include "PacketCapture.h"

PacketCapture::PacketCapture(const std::string& interface) {
    sock_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

    this->interface = interface;

    struct sockaddr_ll sll = {
        .sll_family   = AF_PACKET,
        .sll_protocol = htons(ETH_P_ALL),
        .sll_ifindex  = if_nametoindex(this->interface.c_str()),
    };

    bind(sock_fd, (struct sockaddr *)&sll, sizeof(sll));

    // set promsicious mode
    struct packet_mreq mreq = {
        .mr_ifindex = if_nametoindex("eth0"),
        .mr_type    = PACKET_MR_PROMISC,
    };

    setsockopt(sock_fd, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
};
