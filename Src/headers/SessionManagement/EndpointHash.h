#pragma once
#include "Endpoint.h"
#include <cstddef>
#include <cstdint>
#include <functional>

struct EndpointHash
{
    std::size_t operator()(const Endpoint& endpoint) const {
        return std::hash<uint32_t>()(endpoint.ip) ^ std::hash<uint16_t>()(endpoint.port);
    }
};