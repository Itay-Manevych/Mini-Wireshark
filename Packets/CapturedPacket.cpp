#include "CapturedPacket.h"

void CapturedPacket::AddLayer(std::unique_ptr<Packet> layer) {
    layers.push_back(std::move(layer));
}

void CapturedPacket::PrintInformation(std::ostream& os, size_t packet_number) const {
    os << "---------------------------------------------------------------------------------------------------------------------------" << std::endl;

    if (packet_number != 0) {
        os << "[" << packet_number << "] ";
    }

    for (int i = 0; i < layers.size(); i++) {
        if (i > 0) {
            os << " | ";
        }
        
        layers[i]->PrintInformation(os);
    }

    os << std::endl << "---------------------------------------------------------------------------------------------------------------------------" << std::endl;
}