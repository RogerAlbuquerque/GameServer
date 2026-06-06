#pragma once

#include "PacketHeader.h"

struct ConnectAcceptedPacket
{
    PacketHeader header;

    uint32_t playerId;
};