#pragma once

#include "Packet.h"

#include <vector>
#include <cstdint>

class TcpLayer : public Packet {
    public:
        TcpLayer(const std::vector<uint8_t>& payload);

        virtual void PrintInformation(std::ostream& os) const override;

    private:
        uint16_t source_port;
        uint16_t destination_port;
        
        uint32_t seq_number;
        uint32_t ack_number;

        uint8_t header_length;

        std::vector<uint8_t> data;
};