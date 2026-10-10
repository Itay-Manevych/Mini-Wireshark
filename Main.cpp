#include <iostream>
#include <thread>
#include "PacketCapture.h"

int main() {
    PacketCapture packet("eth0");

    std::thread captureThread([&packet]() {
        packet.StartCapture();
    });

    std::cout << "Press Any Key to stop capturing..." << std::endl;
    std::cin.get();

    packet.StopCapture();
    captureThread.join();
}