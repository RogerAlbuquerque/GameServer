#pragma once
#include <cstdint>
struct Endpoint
{
    std::uint32_t ip;
    uint16_t port;

    bool operator==(const Endpoint& other) const
    {
        return ip == other.ip && port == other.port;
    }
};

