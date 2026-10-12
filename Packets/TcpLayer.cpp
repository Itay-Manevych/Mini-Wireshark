#include "TcpLayer.h"

TcpLayer::TcpLayer(const std::vector<uint8_t>& payload) {
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

    if (header_length < 20 || header_length > payload.size()) {
        throw std::invalid_argument("Invalid TCP header length");
    }

    flags = payload[13];

    data.assign(
        payload.begin() + header_length,
        payload.end()
    );
}

void TcpLayer::PrintInformation(std::ostream& os) const {
    os << "TCP ";
    os << source_port << " -> " << destination_port 
    << ", SEQ = " << "[" << seq_number << "]" 
    << ", ACK = " << "[" << ack_number << "]" 
    << ", FLAGS = " << "[" << GetFlagsAsText() << "]" << std::endl;

    if (data.size() == 0) {
        return;
    }

    os << "Data: ";
    for (size_t i = 0; i < data.size(); i++) {
        os << data[i];
    }
}

std::string TcpLayer::GetFlagsAsText() const {
    std::string result;

    auto AppendString = [&result](const std::string& name) {
        if (!result.empty()) {
            result += " , " + name;
        }

        result += name;
    };

    if (flags & 0x02) {
        AppendString("SYN");
    }

    if (flags & 0x10) {
        AppendString("ACK");
    }

    if (flags & 0x01) {
        AppendString("FIN");
    }

    if (flags & 0x04) {
        AppendString("RST");
    }

    if (flags & 0x08) {
        AppendString("PSH");
    }

    if (flags & 0x20) {
        AppendString("URG");
    }

    if (flags & 0x40) {
        AppendString("ECE");
    }

    if (flags & 0x80) {
        AppendString("CWR");
    }

    return result.empty() ? "No Flags" : result;
}
