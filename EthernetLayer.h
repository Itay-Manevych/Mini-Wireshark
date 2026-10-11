#pragma once

#include "Packet.h"

// Linux networking
#include <net/ethernet.h>

// C++
#include <cstdint>
#include <array>
#include <vector>
#include <ostream>

class EthernetLayer : public Packet {
    public:
        EthernetLayer(const uint8_t* source, const uint8_t* destination, const uint16_t next_protocol, const std::vector<uint8_t>& payload);
        virtual void PrintInformation(std::ostream& os) const override;

    private:
        std::array<uint8_t, ETH_ALEN> source;
        std::array<uint8_t, ETH_ALEN> destination;
        uint16_t next_protocol;
        std::vector<uint8_t> payload;

};