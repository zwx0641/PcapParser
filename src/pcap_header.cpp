#include <cstring>

#include "pcap_header.h"

pcap_global_header::pcap_global_header(char* const data) {
    memcpy(this, data, sizeof(pcap_global_header));
}

pcap_packet_header::pcap_packet_header(char* const data) {
    memcpy(this, data, sizeof(pcap_packet_header));
}