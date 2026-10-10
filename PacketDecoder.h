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
#include "EthernetLayer.h"

class PacketDecoder {
    public:
        static void DecodePackets(const std::array<uint8_t, 65536>& buffer, size_t bytes_recieved);
    private:
        void HandlePacketType(const struct ethhdr& eth, const std::vector<uint8_t>& payload);
};