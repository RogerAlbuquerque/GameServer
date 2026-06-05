#pragma once

#include <string>
#include "Transform.h"

struct Npc
{
    uint32_t id;
    std::string name;
    Transform transform;
    float interactionRange;
};