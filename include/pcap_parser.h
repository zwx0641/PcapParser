#pragma once

#include "pcap_header.h"
#include "pcap_reader.h"

template<typename parser_type>
class pcap_parser {
  public:
    pcap_parser(char* const file_path) : file_(fopen(file_path, "rb")) {
        if (file_ == nullptr) {
            std::cout << "File does not exist" << std::endl;
            exit(1);
        }
    };

    ~pcap_parser();

    void parse_pcap();

  private:
    FILE* file_;
};