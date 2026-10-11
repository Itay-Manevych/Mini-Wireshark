#include "IPv4Layer.h"

/*
                          IPv4 HEADER FORMAT

          Byte 0          Byte 1          Byte 2          Byte 3
         bits 0-7       bits 8-15       bits 16-23      bits 24-31
     |               |               |               |               |
Bits 0               8               16              24              32
     +-------+-------+-----------+---+-------------------------------+
  0  |Version|  IHL  |    DSCP   |ECN|          Total Length         |
     +-------+-------+-----------+---+-------------------------------+
  4  |         Identification        |Flags|     Fragment Offset     |
     +-------------------------------+-----+-------------------------+
  8  |      TTL      |    Protocol   |        Header Checksum        |
     +---------------+---------------+-------------------------------+
 12  |                         Source Address                        |
     +---------------------------------------------------------------+
 16  |                      Destination Address                      |
     +---------------------------------------------------------------+
 20  |                      Options (if IHL > 5)                     |
     |                         (Variable)                            |
     +---------------------------------------------------------------+

 Left column = byte offset from start of IPv4 header.
 Each row    = 32 bits = 4 bytes.
 Minimum IPv4 header = 20 bytes.
 Maximum IPv4 header = 60 bytes.
*/

IPv4Layer::IPv4Layer(const std::vector<uint8_t>& payload) {
    header_length = payload[0] & 0x0F;

    total_length = (static_cast<uint16_t>(payload[2]) << 8) | payload[3];
    identification = (static_cast<uint16_t>(payload[4]) << 8) | payload[5];
    fragmenetation = (static_cast<uint16_t>(payload[6]) << 8) | payload[7];

    ttl = payload[8];
    protocol = payload[9];

    source = static_cast<uint32_t>(payload[12] << 24) 
            | static_cast<uint32_t>(payload[13] << 16) 
            | static_cast<uint16_t>(payload[14] << 8)
            | payload[15];

    destination = static_cast<uint32_t>(payload[16] << 24) 
        | static_cast<uint32_t>(payload[17] << 16) 
        | static_cast<uint16_t>(payload[18] << 8)
        | payload[19];
}

void IPv4Layer::PrintInformation(std::ostream& os) const {
    auto PrintIP = [&os](uint32_t ip) {
        os << (ip >> 24 & 0xFF) << "."
        << (ip >> 16 & 0xFF) << "."
        << (ip >> 8 & 0xFF) << "."
        << (ip & 0xFF);
    };

    os << std::dec;
    os << "IPV4 ";

    PrintIP(source);
    os << " -> ";
    PrintIP(destination);
}

uint32_t IPv4Layer::GetSource() const {
    return source;
}

uint32_t IPv4Layer::GetDestination() const {
    return destination;
}

uint16_t IPv4Layer::GetTotalPacketLength() const {
    return total_length;
}

uint16_t IPv4Layer::GetIdentification() const {
    return identification;
}

uint16_t IPv4Layer::GetFragmentation() const {
    return fragmenetation;
}

uint8_t IPv4Layer::GetTTL() const {
    return ttl;
}

uint8_t IPv4Layer::GetProtocol() const {
    return protocol;
}

uint8_t IPv4Layer::GetHeaderLength() const {
    return header_length;
}