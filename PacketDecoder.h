#pragma once
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <system_error>
#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <array>
#include <cstring>
#include <iomanip>

class PacketDecoder {
    public:
        PacketDecoder(int sock_fd);
        void DecodePackets();
    private:
        int sock_fd;
};