#pragma once

#include <cstdint>
#include <iostream>
#include <string>

namespace Simba
{

struct MDPacketHeader
{
    bool incremental() const
    {
        return msgFlags & 0x8;
    }

    uint32_t msgSeqNum;
    uint16_t msgSize;
    uint16_t msgFlags;
    uint64_t sendingTime;
} __attribute__((packed));

struct IncrementalPacketHeader
{
    uint64_t transactTime;
    uint32_t exchangeTradingSessionID;
} __attribute__((packed));

struct MsgHeader
{
    uint16_t blockLength;
    uint16_t templateID;
    uint16_t schemaID;
    uint16_t version;
};

struct GroupSize
{
    uint16_t blockLength;
    uint8_t numInGroup;
} __attribute__((packed));

enum class MDEntryType : char
{
    bid = '0',
    ask = '1',
    empty = 'J'
};

enum class MDUpdateAction : uint8_t
{
    newOrder = 0,
    changeOrder = 1,
    deleteOrder = 2
};

struct OrderUpdate
{
    static constexpr uint16_t MSG_ID = 15;

    int64_t mdEntryID;
    int64_t mdEntryPx;
    int64_t mdEntrySize;
    uint64_t mdFlags;
    uint64_t mdFlags2;
    int32_t securityID;
    uint32_t rtpSeq;
    MDUpdateAction mdUpdateAction;
    MDEntryType mdEntryType;

    const std::string format() const
    {
        return "{\"mdEntryID\" : " + std::to_string(mdEntryID) + ", " + "\"mdEntryPx\" : " + std::to_string(mdEntryPx) +
               ", " + "\"mdEntrySize\" : " + std::to_string(mdEntrySize) + ", " +
               "\"mdFlags\" : " + std::to_string(mdFlags) + ", " + "\"mdFlags2\" : " + std::to_string(mdFlags2) + ", " +
               "\"securityID\" : " + std::to_string(securityID) + ", " + "\"rtpSeq\" : " + std::to_string(rtpSeq) +
               ", " + "\"mdUpdateAction\" : " + std::to_string(uint8_t(mdUpdateAction)) + ", " +
               "\"mdEntryType\" : " + char(mdEntryType) + "}\n";
    }
} __attribute__((packed));

struct OrderExecution
{
    static constexpr uint16_t MSG_ID = 16;

    int64_t mdEntryID;
    int64_t mdEntryPx;
    int64_t mdEntrySize;
    int64_t lastPx;
    int64_t lastQty;
    int64_t tradeID;
    uint64_t mdFlags;
    uint64_t mdFlags2;
    int32_t securityID;
    uint32_t rtpSeq;
    MDUpdateAction mdUpdateAction;
    MDEntryType mdEntryType;

    const std::string format() const
    {
        return "{\"mdEntryID\" : " + std::to_string(mdEntryID) + ", " + "\"mdEntryPx\" : " + std::to_string(mdEntryPx) +
               ", " + "\"mdEntrySize\" : " + std::to_string(mdEntrySize) + ", " +
               "\"lastPx\" : " + std::to_string(lastPx) + ", " + "\"lastQty\" : " + std::to_string(lastQty) + ", " +
               "\"tradeID\" : " + std::to_string(tradeID) + ", " + "\"mdFlags\" : " + std::to_string(mdFlags) + ", " +
               "\"mdFlags2\" : " + std::to_string(mdFlags2) + ", " + "\"securityID\" : " + std::to_string(securityID) +
               ", " + "\"rtpSeq\" : " + std::to_string(rtpSeq) + ", " +
               "\"mdUpdateAction\" : " + std::to_string(uint8_t(mdUpdateAction)) + ", " +
               "\"mdEntryType\" : " + char(mdEntryType) + "}\n";
    }
} __attribute__((packed));

struct OrderBookSnapshot
{
    static constexpr uint16_t MSG_ID = 17;

    uint32_t securityID;
    uint32_t lastMsgSeqNumProcessed;
    uint32_t rptSeq;
    uint32_t exchangeTradingSessionID;
    GroupSize noMDEntries;
    uint64_t mdEntryID;
    uint64_t transactTime;
    uint64_t mdEntryPx;
    uint64_t mdEntrySize;
    uint64_t tradeID;
    uint64_t mdFlags;
    uint64_t mdFlags2;
    MDEntryType mdEntryType;

    const std::string format() const
    {
        return "{\"SecurityID\" : " + std::to_string(securityID) + ", " +
               "\"LastMsgSeqNumProcessed\" : " + std::to_string(lastMsgSeqNumProcessed) + ", " +
               "\"rptSeq\" : " + std::to_string(rptSeq) + ", " +
               "\"exchangeTradingSessionID\" : " + std::to_string(exchangeTradingSessionID) + ", " +
               "\"blockLength\" : " + std::to_string(noMDEntries.blockLength) + ", " +
               "\"numInGroup\" : " + std::to_string(noMDEntries.numInGroup) + ", " +
               "\"mdEntryID\" : " + std::to_string(mdEntryID) + ", " +
               "\"transactTime\" : " + std::to_string(transactTime) + ", " +
               "\"mdEntryPx\" : " + std::to_string(mdEntryPx) + ", " +
               "\"mdEntrySize\" : " + std::to_string(mdEntrySize) + ", " + "\"tradeID\" : " + std::to_string(tradeID) +
               ", " + "\"mdFlags\" : " + std::to_string(mdFlags) + ", " + "\"mdFlags2\" : " + std::to_string(mdFlags2) +
               ", " + "\"mdEntryType\" : " + char(mdEntryType) + "}\n";
    }
} __attribute__((packed));

} // namespace Simba