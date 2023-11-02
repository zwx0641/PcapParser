#pragma once

#include <vector>

#include "Pcap.h"
#include "PcapHeader.h"
#include "Simba/Messages.h"
#include "Simba/SimbaCast.h"
#include "Util/JsonWriter.h"
#include "Util/UDP.h"

namespace Pcap
{

class PcapParser
{
  public:
    PcapParser(const std::string_view filePath, const std::string_view writePath)
        : validFile_(true), pcap_(filePath), json_(writePath)
    {
        parseGlobHeader();
    };

    ~PcapParser();

    Packet parsePcap();

    void parseGlobHeader();

    void applySimba(const Network::UDP &udp);

    [[nodiscard]] const bool valid_file()
    {
        return validFile_;
    };

  private:
    PcapFile pcap_;

    bool validFile_;

    std::vector<char> data_;

    Util::JsonWriter json_;
};

} // namespace Pcap