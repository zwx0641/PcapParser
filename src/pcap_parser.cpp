#include "pcap_parser.h"
#include "simba/messages.h"
#include "pcap_header.h"

template <typename parser_type>
pcap_parser<parser_type>::~pcap_parser() {
    fclose(file_);
}

template <typename parser_type>
void pcap_parser<parser_type>::parse_pcap() {
    pcap_global_header glob_header;
    pcap_packet_header pkt_header;

    const auto gh_bytes = fread(&glob_header, 1, sizeof(glob_header), file_);

    if (!gh_bytes) {
        return;
    }

    while (!feof(file_)) {
        const auto ph_bytes = fread(&pkt_header, 1, sizeof(pkt_header), file_);

        if (!ph_bytes) {
            return;
        }

        uint8_t* packet = (uint8_t*)malloc(pkt_header.incl_length);
        const auto packet_bytes =
            fread(packet, 1, pkt_header.incl_length, file_);

        if (packet_bytes != pkt_header.incl_length) {
            std::cout << "Packet read length " << packet_bytes << " != incl_length " << pkt_header.incl_length << std::endl;
            return;
        }

        // TODO: parse simba protocol
        //const auto snap = parser_type(
        //    reinterpret_cast<char*>(packet + sizeof(net::ipv4_udp_header)));
        
        const auto header = reinterpret_cast<Simba::MsgHeader*>(packet + 42);

        free(packet);
    }
}