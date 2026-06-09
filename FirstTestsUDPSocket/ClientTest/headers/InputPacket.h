#pragma once

#include "PacketHeader.h"

struct InputPacket
{
    PacketHeader header;

    uint8_t inputFlags;
};