#pragma once

#include <cstdint>
#include <netinet/in.h>

struct PlayerSession
{
    uint32_t playerId;

    sockaddr_in endpoint;

    uint64_t lastPacketTime;

    bool connected;
};