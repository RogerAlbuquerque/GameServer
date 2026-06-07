#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>
#include "PlayerSession.h"
#include "Endpoint.h"
#include "EndpointHash.h"

class SessionManager
{
public:

    void AddSession(std::unique_ptr<PlayerSession> session);

    PlayerSession* GetSessionByPlayerId(uint32_t playerId);

    PlayerSession* GetSessionByEndpoint(const Endpoint& endpoint);


private:

    std::unordered_map<uint32_t, std::unique_ptr<PlayerSession>> sessionsByPlayerId;
    //uint32_t = <Id do player>
    std::unordered_map<Endpoint, PlayerSession*, EndpointHash> sessionsByEndpoint;
};