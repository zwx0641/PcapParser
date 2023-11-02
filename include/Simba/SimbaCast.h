#pragma once

#include <cstring>
#include <optional>

namespace Simba
{

template <typename SimbaType> static inline std::optional<SimbaType> cast(const char *data, const size_t dataSize)
{
    SimbaType msg;

    if (dataSize < sizeof(SimbaType))
    {
        return {};
    }

    std::memcpy(&msg, data, sizeof(SimbaType));
    return msg;
}

} // namespace Simba