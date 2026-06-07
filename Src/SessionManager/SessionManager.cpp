#include "SessionManager.h"
#include "PlayerSession.h"
#include "SessionManager.h"

void SessionManager::AddSession(
     std::unique_ptr<PlayerSession> session)

{
    Endpoint endpoint;
    endpoint.ip = session->endpoint.sin_addr.s_addr;
    endpoint.port = session->endpoint.sin_port;
    
    PlayerSession* rawPointer = session.get();

    sessionsByPlayerId[session->playerId] = std::move(session);
    sessionsByEndpoint[endpoint] = rawPointer;
}

PlayerSession* SessionManager::GetSessionByPlayerId(
    uint32_t playerId)
{
    auto it = sessionsByPlayerId.find(playerId);

    if(it == sessionsByPlayerId.end())
        return nullptr;

    return it->second.get();
}


PlayerSession* SessionManager::GetSessionByEndpoint(const Endpoint& endpoint)
{
     auto it = sessionsByEndpoint.find(endpoint);

      if(it == sessionsByEndpoint.end())
        return nullptr;
 
       return it->second;
}