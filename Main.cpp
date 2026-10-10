#include <iostream>
#include <thread>
#include "PacketCapture.h"

int main() {
    PacketCapture packet("eth0");

    std::thread captureThread([&packet]() {
        packet.StartCapture();
    });

    sleep(1);
    std::cout << "Press Enter to stop capturing..." << std::endl;
    std::cin.get();

    packet.StopCapture();
    captureThread.join();
}