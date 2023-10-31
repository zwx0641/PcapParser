#pragma once

#include <fstream>
#include <stdexcept>

namespace Pcap {

class PcapFile {

public:

    PcapFile(const std::string_view filePath) {
        file_.open(filePath.data(), std::ios::in | std::ios::binary);

        if (!file_.is_open()) {
            throw std::runtime_error("Failed to open file");
        }
    }

    const bool eof() {
        return file_.eof();
    }

    size_t read(void* s, const size_t size) {
        return file_.read(reinterpret_cast<char*>(s), size).gcount();
    }

    ~PcapFile() {
        file_.close();
    }

private:

    std::ifstream file_;

};

class Packet {

public:
    Packet() = default;

    Packet(const char* data, const size_t size) : data_(data), size_(size) {}

    const char* data() const {
        return data_;
    }

    size_t size() const {
        return size_;
    }

    const bool valid() {
        return data_ != nullptr;
    }

private:

    const char* data_{nullptr};

    size_t size_{0};
};

};