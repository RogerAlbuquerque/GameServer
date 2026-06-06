#pragma once

#include <cstdint>

enum InputFlags : uint8_t
{
    None     = 0,

    Up       = 1 << 0,

    Down     = 1 << 1,

    Left     = 1 << 2,

    Right    = 1 << 3,

    Interact = 1 << 4
};