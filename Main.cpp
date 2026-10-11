#include "Capture/PacketCapture.h"

int main() {
    PacketCapture packet("eth0", std::cout);

    packet.StartCapture();

    std::cout << "Press Enter to stop capturing..." << std::endl;
    std::cin.get();

    packet.StopCapture();
}