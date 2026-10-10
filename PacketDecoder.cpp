#include "PacketDecoder.h"

PacketDecoder::PacketDecoder(int sock_fd) : sock_fd(sock_fd) {};

void PacketDecoder::DecodePackets() {
    

        /* buf[0..13]: Ethernet header
        buf[0..5]:  destination MAC
        buf[6..11]: source MAC
        buf[12..13]: EtherType (0x0800=IPv4, 0x0806=ARP, 0x86DD=IPv6)
        buf[14..n-1]: payload */

        // struct ethhdr eth{};
        // std::memcpy(&eth, buffer.data(), sizeof(eth));
        // std::vector<uint8_t> payload(
        //     buffer.begin() + sizeof(eth),
        //     buffer.begin() + bytes_recieved
        // );
        // EthernetPacket packet(eth.h_source, eth.h_dest, eth.h_proto, payload);
        // packet.PrintPacketInformation(std::cout);
    
}