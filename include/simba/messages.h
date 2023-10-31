#pragma once

#include <cstdint>

namespace Simba {
    struct MsgHeader {
        uint16_t blockLength;
        uint16_t templateId;
        uint16_t schemaId;
        uint16_t version;
    };

    struct OrderBookSnapshot {
        struct {
            uint32_t securityID;
            uint32_t lastMsgSeqNumProcessed;
            uint32_t rptSeq;
            uint32_t exchangeTradingSessionID;
            struct {
                uint16_t blockLength;
                uint8_t numInGroup;
            } noMDEntries;
            uint64_t mdEntryID;
            uint64_t transactTime;
            uint64_t mdEntryPx;
            uint64_t mdEntrySize;
            uint64_t tradeId;
            uint64_t mdFlags;
            uint64_t mdFlags2;
            uint8_t mdEntryType;
        } msg;

        OrderBookSnapshot(char* const data);

        void print_msg();
    };
}