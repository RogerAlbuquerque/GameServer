#pragma once

#include <unordered_map>
#include "PlayerSession.h"

class SessionManager
{
public:

    void AddSession(const PlayerSession& session);

    PlayerSession* GetSession(uint32_t playerId);

private:

    std::unordered_map<uint32_t, PlayerSession> sessions;
};