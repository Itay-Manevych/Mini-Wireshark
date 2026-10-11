#pragma once

#include "Packets/CapturedPacket.h"

#include <array>
#include <vector>
#include <optional>
#include <cstdint>
#include <cstddef>

struct ethhdr;

class PacketDecoder {
    public:
        static std::optional<CapturedPacket> DecodePackets(const std::array<uint8_t, 65536>& buffer, size_t bytes_recieved);
        
    private:
        static std::optional<CapturedPacket> HandlePacketType(const struct ethhdr& eth, const std::vector<uint8_t>& payload);
};