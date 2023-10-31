#pragma once

#include <iostream>

#include "Pcap.h"

namespace Pcap::Network {

static constexpr uint8_t UDP_PROTOCOL = 17;

struct MACHeader {
    enum : uint16_t {
        ip = 0x0800,
        vlan = 0x8100
    };

    uint8_t ipAddr[6];
    uint8_t macAddr[6];
    uint16_t type;
    // 14
};

struct IPHeader {
    uint ihl:4;
    uint version:4;
    uint8_t typeOfService;
    uint16_t totalLen;
    uint16_t identification;
    uint16_t fragOffset;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t checksum;
    uint32_t srcAddr;
    uint32_t destAddr;
    // 20
};

struct UDPHeader {
    uint16_t srcPort;
    uint16_t destPort;
    uint16_t length;
    uint16_t checksum;
    // 8
};

class UDP {

public:
    UDP() = default;

    ~UDP() {
    }

    UDP(const Packet& packet) {
        size_t offset = 0;
        const MACHeader* mac = reinterpret_cast<const MACHeader*>(packet.data() + offset);
        offset += sizeof(MACHeader);

        if (packet.size() < offset + sizeof(IPHeader)) {
            std::cout << "Packet size not enough to get ip header" << std::endl;
            return;
        }

        ip_ = reinterpret_cast<const IPHeader*>(packet.data() + offset);
        if (ip_->protocol != UDP_PROTOCOL) {
            std::cout << "Not supported protocol" << std::endl;
            return;
        }

        offset += sizeof(IPHeader);

        if (packet.size() < offset + sizeof(UDPHeader)) {
            std::cout << "Packet size not enough to get udp header" << std::endl;
            return;
        }

        udp_ = reinterpret_cast<const UDPHeader*>(packet.data() + offset);
        offset += sizeof(UDPHeader);

        data_ = packet.data() + offset;
        size_ = packet.size() - offset;
    };

    const bool valid() {
        return data_ != nullptr;
    }

    [[nodiscard]] const char* data() const {
        return data_;
    }

    const size_t dataSize() const {
        return size_;
    };

private:
    const IPHeader* ip_{nullptr};

    const UDPHeader* udp_{nullptr};

    const char* data_{nullptr};

    size_t size_{0};
};

}