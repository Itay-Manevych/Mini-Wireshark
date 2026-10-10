#pragma once
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <string>
#include <system_error>
#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <atomic>
#include <thread>
#include <sys/time.h>
#include <sys/socket.h>
#include <cerrno>
#include <system_error>

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

        int CreateAndBindSocket();
        void RecievePackets();
};