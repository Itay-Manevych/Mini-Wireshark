#pragma once

#include "CapturedPacket.h"

#include <string>
#include <atomic>
#include <thread>
#include <vector>


class PacketCapture {
    public:
        PacketCapture(const std::string& interface);
        ~PacketCapture();
        void StartCapture();
        void StopCapture();

    private:
        int sock_fd;
        std::string interface;
        std::atomic<bool> is_capturing;
        std::thread capture_thread;
        std::vector<CapturedPacket> captured_packets;

        int CreateAndBindSocket();
        void RecievePackets();
};