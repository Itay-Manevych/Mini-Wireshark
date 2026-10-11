#pragma once

#include "Packet.h"

#include <vector>
#include <memory>

class CapturedPacket {
    public:
        void AddLayer(std::unique_ptr<Packet> layer);
        void PrintInformation(std::ostream& os) const;
        
    private:
        std::vector<std::unique_ptr<Packet>> layers;
};