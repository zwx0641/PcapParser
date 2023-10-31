#pragma once

#include <vector>

#include "PcapHeader.h"
#include "Pcap.h"
#include "Util/UDP.h"
#include "Util/JsonWriter.h"
#include "Simba/Messages.h"
#include "Simba/SimbaCast.h"

namespace Pcap {

class PcapParser {
public:
    PcapParser(const std::string_view filePath, const std::string_view writePath)
        : validFile_(true), pcap_(filePath), json_(writePath) {
        parseGlobHeader();
    };

    ~PcapParser();

    Packet parsePcap();

    void parseGlobHeader();

    void applySimba(const Network::UDP& udp);

    [[nodiscard]] const bool valid_file() { return validFile_; };

private:
    PcapFile pcap_;

    bool validFile_;

    std::vector<char> data_;

    Util::JsonWriter json_;
};

}