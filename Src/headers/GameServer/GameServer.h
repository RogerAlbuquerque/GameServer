#pragma once

#include "UdpSocket.h"
#include "World.h"
#include "SessionManager.h"

class GameServer
{
    public:

        bool Start();

        void Run();
    
    private:

        void receivePackets();

        void updateGame();

        void sendSnapshot();

        void handleConnect(const sockaddr_in& clientAddr);

        void handleInput(
            const sockaddr_in& clientAddr,
            const char* buffer,
            int bytes
        );

        void handleInteract();
        
        void handleDisconnect();
        
    private:

        UdpSocket socket;

        World world;

        SessionManager sessionManager;

        uint32_t nextPlayerId = 0;
};