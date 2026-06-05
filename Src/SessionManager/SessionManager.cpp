#include "SessionManagement/SessionManager.h"

void SessionManager::AddSession(
    const PlayerSession& session)
{
    sessions[session.playerId] = session;
}

PlayerSession* SessionManager::GetSession(
    uint32_t playerId)
{
    auto it = sessions.find(playerId);

    if(it == sessions.end())
        return nullptr;

    return &it->second;
}