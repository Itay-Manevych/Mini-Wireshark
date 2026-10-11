#include "PacketDecoder.h"

#include "Packets/EthernetLayer.h"
#include "Packets/IPv4Layer.h"
#include "Packets/UdpLayer.h"

// Linux networking
#include <net/ethernet.h>
#include <arpa/inet.h>

// C++
#include <cstring>
#include <memory>
#include <stdexcept>

std::optional<CapturedPacket> PacketDecoder::DecodePackets(const std::array<uint8_t, 65536>& buffer, size_t bytes_recieved) {
    if (bytes_recieved > buffer.size()) {
        throw std::invalid_argument("Packet length is too big");
    }

    if (bytes_recieved < sizeof(struct ethhdr)) {
        return std::nullopt; // skip invalid packets
    }

    /* buf[0..13]: Ethernet header
    buf[0..5]:  destination MAC
    buf[6..11]: source MAC
    buf[12..13]: EtherType (0x0800=IPv4, 0x0806=ARP, 0x86DD=IPv6)
    buf[14..n-1]: payload */

    struct ethhdr eth{};
    std::memcpy(
        &eth, 
        buffer.data(), 
        sizeof(eth)
    );

    std::vector<uint8_t> payload(
        buffer.begin() + sizeof(eth),
        buffer.begin() + bytes_recieved
    );

    return HandlePacketType(eth, payload);
}

std::optional<CapturedPacket> PacketDecoder::HandlePacketType(const struct ethhdr& eth, const std::vector<uint8_t>& payload) {
    CapturedPacket captured_packet;
    EthernetLayer eth_packet(eth.h_source, eth.h_dest, eth.h_proto, payload);
    captured_packet.AddLayer(std::make_unique<EthernetLayer>(eth_packet));

    switch (ntohs(eth.h_proto)) {
        case ETH_P_IP: { // IPV4
            if (payload.size() < 20) {
                break;
            }
            
            IPv4Layer ipv4_packet(payload);
            captured_packet.AddLayer(std::make_unique<IPv4Layer>(ipv4_packet));

            uint8_t header_length = ipv4_packet.GetHeaderLength() * 4;
            uint16_t total_length = ipv4_packet.GetTotalPacketLength();
            uint8_t protocol = ipv4_packet.GetProtocol();

            if (protocol == IPPROTO_UDP) {
                std::vector<uint8_t> udp_payload(
                    payload.begin() + header_length,
                    payload.begin() + total_length
                );
    
                UdpLayer udp_packet(udp_payload);
                captured_packet.AddLayer(std::make_unique<UdpLayer>(udp_packet));
            }

            break;
        }
        
        case ETH_P_IPV6: { // IPV6
            break;
        }

        case ETH_P_ARP: { // ARP
            break;
        }
    }
    return captured_packet;
}