#include "PacketDecoder.h"

PacketDecoder::PacketDecoder(int sock_fd) : sock_fd(sock_fd) {};

void PacketDecoder::DecodePackets() {
    std::array<uint8_t, 65536> buffer;

    struct sockaddr_ll src_addr;
    socklen_t addr_len = sizeof(src_addr);

    while (true) {
        ssize_t bytes_recieved = recvfrom(
        sock_fd, 
        buffer.data(), 
        buffer.size(), 
        0, 
        reinterpret_cast<struct sockaddr *>(&src_addr), 
        &addr_len);

        if (bytes_recieved == -1) {
            close(sock_fd);
            throw std::system_error(errno, std::generic_category(), "recvfrom failed while trying to decode packets");
        }

        if(static_cast<size_t>(bytes_recieved) < sizeof(struct ethhdr)) {
            close(sock_fd);
            throw std::system_error(errno, std::generic_category(), "not enough bytes recieved while trying to decode packets");
        }

        /* buf[0..13]: Ethernet header
        buf[0..5]:  destination MAC
        buf[6..11]: source MAC
        buf[12..13]: EtherType (0x0800=IPv4, 0x0806=ARP, 0x86DD=IPv6)
        buf[14..n-1]: payload */

        struct ethhdr eth{};
        std::memcpy(&eth, buffer.data(), sizeof(eth));
        std::vector<uint8_t> payload(
            buffer.begin() + sizeof(eth),
            buffer.begin() + bytes_recieved
        );
        EthernetPacket packet(eth.h_source, eth.h_dest, eth.h_proto, payload);
        packet.PrintPacketInformation(std::cout);
    }
}