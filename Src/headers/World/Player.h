#pragma once

#include <cstdint>
#include "Transform.h"
#include "InputState.h"

struct Player
{
    uint32_t id;
    Transform transform;
    InputState input;

    void Update(float deltaTime);
};