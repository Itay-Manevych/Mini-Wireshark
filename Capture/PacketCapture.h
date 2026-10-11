#pragma once

#include "Packets/CapturedPacket.h"

#include <string>
#include <atomic>
#include <thread>
#include <vector>
#include <iostream>

class PacketCapture {
    public:
        PacketCapture(const std::string& interface, std::ostream& os);
        ~PacketCapture();
        void StartCapture();
        void StopCapture();

    private:
        int sock_fd;
        std::string interface;
        std::atomic<bool> is_capturing;
        std::thread capture_thread;
        std::vector<CapturedPacket> captured_packets;
        std::ostream& os;

        int CreateAndBindSocket();
        void RecievePackets();
};