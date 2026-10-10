#pragma once
#include <iostream>

class Packet {
    public:
        virtual ~Packet() = default;
        virtual void PrintInformation(std::ostream& os) const = 0;
};