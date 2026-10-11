#include "UdpLayer.h"

UdpLayer::UdpLayer(const std::vector<uint8_t>& payload) {
    source_port = (static_cast<uint16_t>(payload[0]) << 8) | payload[1];

    destination_port = (static_cast<uint16_t>(payload[2]) << 8) | payload[3];

    total_length = (static_cast<uint16_t>(payload[4]) << 8) | payload[5];
}

void UdpLayer::PrintInformation(std::ostream& os) const {
    os << "UDP ";
    os << source_port << " -> " << destination_port;
}


uint16_t UdpLayer::GetSourcePort() {
    return source_port;
}

uint16_t UdpLayer::GetDestinationPort() {
    return destination_port;
}

uint16_t UdpLayer::GetTotalLength() {
    return total_length;
}
    