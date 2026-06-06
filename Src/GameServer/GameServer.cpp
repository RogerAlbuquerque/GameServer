#include "GameServer.h"
#include "UdpSocket.h"

bool GameServer::Start()
{
    return socket.Start(7777);
}

void GameServer::Run()
{
    while(true)
    {
        receivePackets();

        // updateGame();

        // sendSnapshots();
    }
}

void GameServer::receivePackets()
{
    char buffer[1024];

    sockaddr_in clientAddr;

    int bytes = socket.Receive(buffer, sizeof(buffer), clientAddr);

    if(bytes <= 0)
        return;
    
    switch(packetType)
    {
        case Connect:
            handleConnect(clientAddr);
            break;

        case Input:
            handleInput();
            break;
    }
    
    // interpretar pacote e enviar para algum lugar depois
    socket.Send(buffer, bytes, clientAddr);
}

void GameServer::handleConnect(
    const sockaddr_in& clientAddr)
{
    Player player;

    player.id = 2; // nextPlayerId -> tem que ser isso na verdade, invés de 2

    world.AddPlayer(player);

    PlayerSession session;

    session.playerId = player.id;
    session.endpoint = clientAddr;
    session.connected = true;

    sessionManager.AddSession(session);
}

void GameServer::handleInput()
{
    
}

void GameServer::handleInteract()
{
    
}

void GameServer::handleDisconnect()
{
    
}