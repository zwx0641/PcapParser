#include <cstring>
#include <iostream>

#include "simba/messages.h"

namespace Simba {
OrderBookSnapshot::OrderBookSnapshot(char* const data) {
    memcpy(&msg, data + 8, sizeof(OrderBookSnapshot));
    print_msg();
}

void OrderBookSnapshot::print_msg() {
    std::cout << " " << msg.securityID
              << " " << msg.lastMsgSeqNumProcessed
              << " " << msg.rptSeq
              << " " << msg.exchangeTradingSessionID
              << " " << msg.noMDEntries.blockLength
              << " " << msg.noMDEntries.numInGroup
              << " " << msg.mdEntryID
              << " " << msg.transactTime
              << " " << msg.mdEntryPx
              << " " << msg.mdEntrySize
              << " " << msg.tradeId
              << " " << msg.mdFlags
              << " " << msg.mdFlags2
              << " " << msg.mdEntryType << std::endl;
}

}