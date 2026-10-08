#include "PacketCapture.h"
#include "PacketDecoder.h"

PacketCapture::PacketCapture(const std::string& interface) : interface(interface) {
};

void PacketCapture::StartCapture() {
    sock_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

    if (sock_fd == -1) {
        throw std::system_error(errno, std::generic_category(), "failed to open a socket");
    }

    this->interface = interface;

    unsigned int index = if_nametoindex(this->interface.c_str()); // interface's index (each interface has an identifiable index)
    if (index == 0) {
        close(sock_fd);

        throw std::system_error(errno, std::generic_category(), "failed to find interface name");
    } 

    int if_index = static_cast<int>(index);
    struct sockaddr_ll sll = { // link layer socket address
        .sll_family   = AF_PACKET,
        .sll_protocol = htons(ETH_P_ALL),
        .sll_ifindex  = if_index,
    };

    int res = bind(sock_fd, reinterpret_cast<struct sockaddr *>(&sll), sizeof(sll));
    if (res == -1) {
        close(sock_fd);

        throw std::system_error(errno, std::generic_category(), "failed to bind the socket");
    }

    // set promsicious mode
    struct packet_mreq mreq = {
        .mr_ifindex = if_index,
        .mr_type    = PACKET_MR_PROMISC,
    };

    setsockopt(sock_fd, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &mreq, sizeof(mreq));

    std::cout << "Succesfully started packet capturing" << std::endl;

    PacketDecoder decoder(sock_fd);
    decoder.DecodePackets();
};

void PacketCapture::StopCapture() {
    close(sock_fd);

    std::cout << "Stopping capture..." << std::endl;
}