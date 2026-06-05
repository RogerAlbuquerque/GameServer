#pragma once

#include <cstdint>

#ifdef _WIN32
#include <winsock2.h>
#endif

struct PlayerSession
{
    uint32_t playerId;

    // sockaddr_in endpoint;

    uint64_t lastPacketTime;

    bool connected;
};