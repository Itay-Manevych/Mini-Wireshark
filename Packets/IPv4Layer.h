#pragma once

#include "Packet.h"

#include <vector>
#include <cstdint>

class IPv4Layer : public Packet {
    public:
        IPv4Layer(const std::vector<uint8_t>& payload);

        virtual void PrintInformation(std::ostream& os) const override;
        
        uint32_t GetSource() const;
        uint32_t GetDestination() const;

        uint16_t GetTotalPacketLength() const;
        uint16_t GetIdentification() const;
        uint16_t GetFragmentation() const;

        uint8_t GetTTL() const;
        uint8_t GetProtocol() const;
        uint8_t GetHeaderLength() const;

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