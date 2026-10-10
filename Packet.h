#pragma once
#include <iostream>

class Packet {
    public:
        virtual ~Packet();
        virtual const void PrintInformation() = 0;
};