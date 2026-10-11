#pragma once
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <system_error>
#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <array>
#include <vector>
#include <cstring>
#include <iomanip>
#include <stdexcept>
#include <memory>
#include <optional>
#include "EthernetLayer.h"
#include "IPv4Layer.h"
#include "CapturedPacket.h"

class PacketDecoder {
    public:
        static std::optional<CapturedPacket> DecodePackets(const std::array<uint8_t, 65536>& buffer, size_t bytes_recieved);
    private:
        static std::optional<CapturedPacket> HandlePacketType(const struct ethhdr& eth, const std::vector<uint8_t>& payload);
};