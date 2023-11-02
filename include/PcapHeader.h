#pragma once

#include <cstdint>

namespace Pcap
{

static constexpr const uint32_t MS_MAGIC = 0xa1b2c3d4;
static constexpr const std::uint32_t NS_MAGIC = 0xa1b23c4d;

struct PcapGlobalHeader
{
    uint32_t magic_number;
    uint16_t version_major;
    uint16_t version_minor;
    uint32_t timezone;
    uint32_t time_accuracy;
    uint32_t snap_length;
    uint32_t link_layer_type;
    PcapGlobalHeader(){};
};

struct PcapPacketHeader
{
    uint32_t ts_second;
    uint32_t ts_usecond;
    uint32_t incl_length;
    uint32_t original_length;
    PcapPacketHeader(){};
};

namespace net
{
struct ipv4_udp_header
{
    char header[42];
};
} // namespace net

} // namespace Pcap