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

class PacketCapture {
    public:
        PacketCapture(const std::string& interface);
        void StartCapture();
        void StopCapture();
    private:
        int sock_fd;
        std::string interface;
};