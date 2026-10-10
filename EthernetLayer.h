#pragma once
#include "Packet.h"
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <cstdint>
#include <cstring>
#include <vector>
#include <array>
#include <iostream>
#include <iomanip>


class EthernetLayer : Packet {
    public:
        EthernetLayer(const uint8_t* source, const uint8_t* destination, const uint16_t next_protocol, const std::vector<uint8_t>& payload);
        virtual void PrintInformation(std::ostream& os);

    private:
        std::array<uint8_t, ETH_ALEN> source;
        std::array<uint8_t, ETH_ALEN> destination;
        uint16_t next_protocol;
        std::vector<uint8_t> payload;

};