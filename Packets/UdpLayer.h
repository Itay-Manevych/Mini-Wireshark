#pragma once

#include "Packet.h"

#include <vector>
#include <cstdint>

class UdpLayer : public Packet {
    public:
        UdpLayer(const std::vector<uint8_t>& payload);
        virtual void PrintInformation(std::ostream& os) const override;

        uint16_t GetSourcePort();
        uint16_t GetDestinationPort();
        uint16_t GetTotalLength();
    
    private:
        uint16_t source_port;
        uint16_t destination_port;
        uint16_t total_length;
};