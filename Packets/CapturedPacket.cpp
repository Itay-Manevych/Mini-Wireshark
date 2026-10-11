#include "CapturedPacket.h"

void CapturedPacket::AddLayer(std::unique_ptr<Packet> layer) {
    layers.push_back(std::move(layer));
}

void CapturedPacket::PrintInformation(std::ostream& os) const {
    for (const auto& layer : layers) {
        layer->PrintInformation(os);
    }
}