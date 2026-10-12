#pragma once

#include "Packet.h"

#include <vector>
#include <cstdint>

class UdpLayer : public Packet {
    public:
        UdpLayer(const std::vector<uint8_t>& payload);
        virtual void PrintInformation(std::ostream& os) const override;

        uint16_t GetSourcePort() const;
        uint16_t GetDestinationPort() const;
        uint16_t GetTotalLength() const;
        uint16_t GetChecksum() const;
        std::vector<uint8_t> GetData() const;
    
    private:
        uint8_t header_length;

        uint16_t source_port;
        uint16_t destination_port;
        uint16_t total_length;
        uint16_t checksum;

        std::vector<uint8_t> data;
};