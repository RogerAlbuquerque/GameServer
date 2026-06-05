#pragma once

#include <unordered_map>
#include "Player.h"
#include "Npc.h"

class World
{
    public:

        void AddPlayer(const Player& player);

        Player* GetPlayer(uint32_t id);

        void AddNpc(const Npc& npc);

        Npc* GetNpc(uint32_t id);

    public: // Precisa ser private, public só por enquanto

        std::unordered_map<uint32_t, Player> players;

        std::unordered_map<uint32_t, Npc> npcs;
};