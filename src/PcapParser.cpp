#include "PcapParser.h"
#include "PcapHeader.h"
#include "Simba/Messages.h"
#include "SimbaCast.h"


namespace Pcap {

PcapParser::~PcapParser() {
}

Packet PcapParser::parsePcap() {
    PcapPacketHeader pkt_header;
    const size_t ph_bytes = pcap_.read(&pkt_header, sizeof(pkt_header));

    if (ph_bytes != sizeof(pkt_header)) {
        if (ph_bytes) {
            throw std::runtime_error("Pcap Packet header read error");
        }
        return Packet{};
    }

    if (pkt_header.incl_length > data_.size()) {
        throw std::runtime_error("Packet too big");
    }

    const auto pkt_bytes = pcap_.read(data_.data(), pkt_header.incl_length);

    if (pkt_bytes != pkt_header.incl_length) {
        throw std::runtime_error("Pcap Packet read error");
    }

    return Packet{data_.data(), pkt_header.incl_length};
}

void PcapParser::parseGlobHeader() {
    PcapGlobalHeader glob_header;

    const auto gh_bytes = pcap_.read(&glob_header, sizeof(glob_header));

    if (!gh_bytes || gh_bytes != sizeof(glob_header)) {
        throw std::runtime_error("Pcap global header read error");
    }

    data_.resize(glob_header.snap_length);
}

void PcapParser::applySimba(const Network::UDP& udp) {
    size_t offset = 0;
    const auto mdHeader = Simba::cast<Simba::MDPacketHeader>(udp.data(), udp.dataSize());

    if (!mdHeader.has_value()) {
        std::cout << "Packet size not enough for md header" << std::endl;
        return;
    }

    offset += sizeof(Simba::MDPacketHeader);
    
    std::string output;
    if (mdHeader->incremental()) {
        const auto incHeader = 
            Simba::cast<Simba::IncrementalPacketHeader>(udp.data() + offset, udp.dataSize() - offset);

        if (!incHeader.has_value()) {
            std::cout << "Packet size not enough for incr header" << std::endl;
            return;
        }

        offset += sizeof(Simba::IncrementalPacketHeader);

        const auto msgHeader = Simba::cast<Simba::MsgHeader>(udp.data() + offset, udp.dataSize() - offset);
        if (!incHeader.has_value()) {
            std::cout << "Packet size not enough for msg header" << std::endl;
            return;
        }

        offset += sizeof(Simba::MsgHeader);
        switch (msgHeader->templateID) {
            case Simba::OrderUpdate::MSG_ID: {
                const auto update = 
                    Simba::cast<Simba::OrderUpdate>(udp.data() + offset, udp.dataSize() - offset);
                output = update->format();
                break;
            }
            case Simba::OrderExecution::MSG_ID: {
                const auto execution = 
                    Simba::cast<Simba::OrderExecution>(udp.data() + offset, udp.dataSize() - offset);
                output = execution->format();
                break;
            }
            default: {
                return;
            }
        }
    } else {
        const auto msgHeader = Simba::cast<Simba::MsgHeader>(udp.data() + offset, udp.dataSize() - offset);
        if (!msgHeader.has_value()) {
            std::cout << "Packet size not enough for msg header" << std::endl;
            return;
        }

        offset += sizeof(Simba::MsgHeader);
        switch (msgHeader->templateID) {
            case Simba::OrderBookSnapshot::MSG_ID:
                const auto snapshot = 
                    Simba::cast<Simba::OrderBookSnapshot>(udp.data() + offset, udp.dataSize() - offset);
                output = snapshot->format();
        }
    }
    json_.write(output.c_str());
}

}