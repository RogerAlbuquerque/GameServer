#pragma once

#include <cstdint>

enum class PacketType : uint8_t
{
    Connect = 1,

    ConnectAccepted = 2,

    Input = 3,

    Disconnect = 4,

    DialogueStart = 5,

    DialogueNext = 6,

    Snapshot = 7
};