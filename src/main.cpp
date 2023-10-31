#include "pcap_parser.h"
#include "simba/messages.h"
#include "pcap_parser.cpp"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Missing file path" << std::endl;
        return 0;
    }

    pcap_parser<Simba::OrderBookSnapshot> parser(argv[1]);
    parser.parse_pcap();
}