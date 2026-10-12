#include "UdpLayer.h"

UdpLayer::UdpLayer(const std::vector<uint8_t>& payload) {
    if (payload.size() < 8) {
        throw std::invalid_argument("Invalid UDP header");
    }

    header_length = 8;

    source_port = static_cast<uint16_t>(payload[0]) << 8 | payload[1];

    destination_port = static_cast<uint16_t>(payload[2]) << 8 | payload[3];

    total_length = static_cast<uint16_t>(payload[4]) << 8 | payload[5];

    checksum = static_cast<uint16_t>(payload[6]) << 8 | payload[7];

    if (total_length < 8 || total_length > payload.size()) {
        throw std::invalid_argument("Invalid UDP length");
    }

    data.assign(
        payload.begin() + header_length, 
        payload.begin() + total_length
    );
}

void UdpLayer::PrintInformation(std::ostream& os) const {
    os << "UDP ";
    os << source_port << " -> " << destination_port << std::endl;

    os << "Data: ";
    for (size_t i = 0; i < data.size(); i++) {
        os << data[i] << " ";
    }
}

uint16_t UdpLayer::GetSourcePort() const {
    return source_port;
}

uint16_t UdpLayer::GetDestinationPort() const {
    return destination_port;
}

uint16_t UdpLayer::GetTotalLength() const {
    return total_length;
}
    
uint16_t UdpLayer::GetChecksum() const {
    return checksum;
}

std::vector<uint8_t> UdpLayer::GetData() const {
    return data;
}
