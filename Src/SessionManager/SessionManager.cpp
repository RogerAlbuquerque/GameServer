#include "SessionManager.h"
#include "PlayerSession.h"
#include "SessionManager.h"

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


PlayerSession* SessionManager::FindByEndpoint(const sockaddr_in& endpoint)
{
    for(auto& [id, session] : sessions)
    {
        if(session.endpoint.sin_addr.s_addr ==
            endpoint.sin_addr.s_addr &&
           session.endpoint.sin_port ==
            endpoint.sin_port)
        {
            return &session;
        }
    }

    return nullptr;
}