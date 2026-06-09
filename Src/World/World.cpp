#include "World.h"

void World::AddPlayer(const Player& player)
{
    players[player.id] = player;
}

Player* World::GetPlayer(uint32_t id)
{
    auto it = players.find(id);

    if (it == players.end())
        return nullptr;

    return &it->second;
}

void World::AddNpc(const Npc& npc)
{
    npcs[npc.id] = npc;
}

Npc* World::GetNpc(uint32_t id)
{
    auto it = npcs.find(id);

    if (it == npcs.end())
        return nullptr;

    return &it->second;
}

std::unordered_map<uint32_t, Player>& World::GetPlayers()
{
    return players;
}