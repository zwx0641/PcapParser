#include "PcapParser.h"
#include "Simba/Messages.h"
#include "Util/UDP.h"

#include "Util/JsonWriter.h"
int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cout << "Missing file path or write path" << std::endl;
        return 0;
    }

    using namespace Pcap;

    PcapParser parser(argv[1], argv[2]);

    while (1)
    {
        auto packet = parser.parsePcap();

        if (!packet.valid())
        {
            break;
        }

        Pcap::Network::UDP udp{packet};
        if (!udp.valid())
        {
            continue;
        }

        parser.applySimba(udp);
    }
}