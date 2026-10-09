#include "EthernetPacket.h"

EthernetPacket::EthernetPacket(const uint8_t* source, const uint8_t* destination, const uint16_t next_protocol, const std::vector<uint8_t>& payload): next_protocol(next_protocol) ,payload(payload) {
    std::memcpy(this->source.data(), source, ETH_ALEN);
    std::memcpy(this->destination.data(), destination, ETH_ALEN);
};

void EthernetPacket::PrintPacketInformation(std::ostream& os) {
    os << std::hex << std::setfill('0');

    os << std::endl << "------------------------------------" << std::endl;
    os << "Source: ";

    for (int i = 0; i < source.size(); i++) {
        os << std::hex << std::setw(2) << static_cast<int>(source[i]);

        if (i != source.size() - 1) {
            std::cout << ":";
        }
    }

    os << std::endl;
    os << "Destination: ";

    for (int i = 0; i < destination.size(); i++) {
        os << std::hex << std::setw(2) << static_cast<int>(destination[i]);

        if (i != destination.size() - 1) {
            os << ":";
        }
    }

    os << std::endl;

    os << "Protocol:";
    os << std::hex << std::setw(4) << ntohs(next_protocol) << std::endl;
    os << "------------------------------------" << std::endl << std::endl;
};