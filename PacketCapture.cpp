#include "PacketCapture.h"
#include "PacketDecoder.h"

// Linux networking
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>

// C++
#include <array>
#include <cstdint>
#include <optional>
#include <iostream>
#include <system_error>
#include <cerrno>
#include <utility>

PacketCapture::PacketCapture(const std::string& interface, std::ostream& os) : interface(interface), os(os), is_capturing(false), sock_fd(-1) {};

PacketCapture::~PacketCapture() {
    StopCapture();
}

int PacketCapture::CreateAndBindSocket() {
    sock_fd = socket(
        AF_PACKET, 
        SOCK_RAW, 
        htons(ETH_P_ALL)
    );

    if (sock_fd == -1) {
        throw std::system_error(
            errno, 
            std::generic_category(), 
            "failed to open a socket"
        );
    }

    unsigned int index = if_nametoindex(this->interface.c_str()); // interface's index (each interface has an identifiable index)
    if (index == 0) {
        close(sock_fd);
        sock_fd = -1;

        throw std::system_error(
            errno, 
            std::generic_category(), 
            "failed to find interface name"
        );
    } 

    int if_index = static_cast<int>(index);
    struct sockaddr_ll bind_addr = { // link layer socket address
        .sll_family   = AF_PACKET,
        .sll_protocol = htons(ETH_P_ALL),
        .sll_ifindex  = if_index,
    };

    int res = bind(sock_fd, reinterpret_cast<struct sockaddr *>(&bind_addr), sizeof(bind_addr));
    if (res == -1) {
        close(sock_fd);
        sock_fd = -1;

        throw std::system_error(
            errno, 
            std::generic_category(), 
            "failed to bind the socket"
        );
    }

    // set promsicious mode
    struct packet_mreq mreq = {
        .mr_ifindex = if_index,
        .mr_type    = PACKET_MR_PROMISC,
    };

    setsockopt(
        sock_fd, 
        SOL_PACKET, 
        PACKET_ADD_MEMBERSHIP, 
        &mreq, 
        sizeof(mreq)
    );

    // set timeout
    struct timeval timeout{};
    timeout.tv_sec = 30;   // 30 seconds
    timeout.tv_usec = 0;  // 0 microseconds

    setsockopt(
        sock_fd, 
        SOL_SOCKET, 
        SO_RCVTIMEO,
        &timeout, 
        sizeof(timeout)
    );

    return sock_fd;
}

void PacketCapture::RecievePackets() {
    std::array<uint8_t, 65536> buffer;

    struct sockaddr_ll packet_addr;
    socklen_t packet_addr_len = sizeof(packet_addr);

    while (is_capturing) {
        ssize_t bytes_recieved = recvfrom(
            sock_fd, 
            buffer.data(), 
            buffer.size(), 
            0, 
            reinterpret_cast<struct sockaddr *>(&packet_addr), 
            &packet_addr_len
        );

        if (bytes_recieved == -1) {
            if (errno == EINTR) { // interrupted by a syscall
                continue;
            }

            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                os << "No packets received for 30 seconds. Stopping capture." << std::endl;
                is_capturing = false;
                break;
            }

            throw std::system_error(
                errno, 
                std::generic_category(), 
                "recvfrom failed when trying to receive packets"
            );
        }

        if(!is_capturing) {
            break; // drop packet if StopCapture() has been called
        }

        std::optional<CapturedPacket> captured_packet = PacketDecoder::DecodePackets(buffer, static_cast<size_t>(bytes_recieved));
        if (captured_packet.has_value()) {
            captured_packets.push_back(std::move(*captured_packet));
            captured_packets.back().PrintInformation(os);
        }
    }
}

void PacketCapture::StartCapture() {
    sock_fd = CreateAndBindSocket();

    is_capturing = true;

    os << "Succesfully started packet capturing" << std::endl;

    capture_thread = std::thread([this] () {
        try {
            RecievePackets();
        }
        catch(const std::exception& e) {
            os << "Packet capture failed! Error: " << e.what() << std::endl;
            is_capturing = false;
        }
    });
}

void PacketCapture::StopCapture() {
    if (is_capturing) {
        os << "Stopping capture..." << std::endl;
    }

    is_capturing = false;

    if (capture_thread.joinable()) {
        capture_thread.join();
    }

    if (sock_fd != -1) {
        close(sock_fd);
        sock_fd = -1;
    }
}