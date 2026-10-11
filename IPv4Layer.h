#pragma once

#include "Packet.h"

#include <vector>
#include <cstdint>

class IPv4Layer : public Packet {
    public:
        IPv4Layer(const std::vector<uint8_t>& payload);
        virtual void PrintInformation(std::ostream& os) const override;
    private:
        uint32_t source;
        uint32_t destination;

        uint16_t total_length;
        uint16_t identification;
        uint16_t fragmenetation;

        uint8_t ttl;
        uint8_t protocol;
        uint8_t header_length;
};