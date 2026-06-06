#pragma once

#include "UdpSocket.h"
#include "World.h"
#include "SessionManager.h"

class GameServer
{
public:

    bool Start();

    void Run();

    void receivePackets();

private:

    UdpSocket socket;

    World world;

    SessionManager sessionManager;
};