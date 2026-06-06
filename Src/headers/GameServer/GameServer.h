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

    void handleConnect(const sockaddr_in& clientAddr);

    void handleInput();

    void handleInteract();

    
    void handleDisconnect();
private:

    UdpSocket socket;

    World world;

    SessionManager sessionManager;

    
};