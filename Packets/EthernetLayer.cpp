#include "EthernetLayer.h"

// Linux networking
#include <arpa/inet.h>

// C++
#include <cstring>
#include <iomanip>

EthernetLayer::EthernetLayer(const uint8_t* source, const uint8_t* destination, const uint16_t next_protocol, const std::vector<uint8_t>& payload): next_protocol(next_protocol), payload(payload) {
    std::memcpy(this->source.data(), source, ETH_ALEN);
    std::memcpy(this->destination.data(), destination, ETH_ALEN);
}

void EthernetLayer::PrintInformation(std::ostream& os) const {
    os << std::hex << std::setfill('0');

    os << "Ethernet Header ";

    for (int i = 0; i < source.size(); i++) {
        os << std::hex << std::setw(2) << static_cast<int>(source[i]);

        if (i != source.size() - 1) {
            std::cout << ":";
        }
    }

    os << " -> ";

    for (int i = 0; i < destination.size(); i++) {
        os << std::hex << std::setw(2) << static_cast<int>(destination[i]);

        if (i != destination.size() - 1) {
            os << ":";
        }
    }
}