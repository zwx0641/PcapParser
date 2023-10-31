#pragma once

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "pcap_header.h"

inline void load_pcap_from_file(const char* file_path, FILE* fd) {
    fd = fopen(file_path, "rb");

    if (fd == nullptr) {
        std::cout << "File does not exist" << std::endl;
        exit(1);
    }
}

inline bool read_stream_to_header(FILE* const file,
                                  pcap_global_header* const glob_header,
                                  pcap_packet_header* const pkt_header) {
    const auto gh_bytes = fread(glob_header, sizeof(*glob_header), 1, file);
    const auto ph_bytes = fread(pkt_header, sizeof(*pkt_header), 1, file);

    if (!gh_bytes || !ph_bytes) {
        std::cout << "No more data" << std::endl;
        return false;
    }

    return true;
}