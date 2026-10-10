#include <iostream>
#include <thread>
#include "PacketCapture.h"

int main() {
    PacketCapture packet("eth0");

    packet.StartCapture();

    std::cout << "Press Enter to stop capturing..." << std::endl;
    std::cin.get();

    packet.StopCapture();
}