#include "PacketDecoder.h"

void PacketDecoder::DecodePackets(const std::array<uint8_t, 65536>& buffer, size_t bytes_recieved) {
    if (bytes_recieved > buffer.size()) {
        throw std::invalid_argument("Packet length is too big");
    }

    if (bytes_recieved < sizeof(struct ethhdr)) {
        return; // skip invalid packets
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
}