#pragma once

#include <cstdint>

struct pcap_global_header {
    uint32_t magic_number;
    uint16_t version_major;
    uint16_t version_minor;
    uint32_t timezone;
    uint32_t time_accuracy;
    uint32_t snap_length;
    uint32_t link_layer_type;
    pcap_global_header() {};
    pcap_global_header(char* const data);
};

struct pcap_packet_header {
    uint32_t ts_second;
    uint32_t ts_usecond;
    uint32_t incl_length;
    uint32_t original_length;
    pcap_packet_header() {};
    pcap_packet_header(char* const data);
};

namespace net {
    struct ipv4_udp_header {
        char header[42];
    };
}