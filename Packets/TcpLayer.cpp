#include "TcpLayer.h"

TcpLayer::TcpLayer(const std::vector<uint8_t>& payload, uint16_t total_length) {
    if (payload.size() < 20) {
        throw std::invalid_argument("Invalid TCP header");
    }

    source_port = static_cast<uint16_t>(payload[0]) << 8 | payload[1];
    destination_port = static_cast<uint16_t>(payload[2]) << 8 | payload[3];

    seq_number = static_cast<uint32_t>(payload[4]) << 24 
                | static_cast<uint32_t>(payload[5]) << 16
                | static_cast<uint16_t>(payload[6]) << 8
                | payload[7];
    
    ack_number = static_cast<uint32_t>(payload[8]) << 24
                | static_cast<uint32_t>(payload[9]) << 16 
                | static_cast<uint16_t>(payload[10]) << 8 
                | payload[11];
    
    header_length = (payload[12] >> 4) * 4;

    data.assign(
        payload.begin() + header_length,
        payload.begin() + total_length
    );
}

void TcpLayer::PrintInformation(std::ostream& os) const {
    os << "TCP ";
    os << source_port << " -> " << destination_port 
    << " SEQ = " << seq_number << " ACK = " << ack_number << std::endl;

    os << "Data: ";
    for (size_t i = 0; i < data.size(); i++) {
        os << data[i] << " ";
    }
}
