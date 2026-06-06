#include "GameServer.h"
#include "PacketSystem/InputFlags.h"
#include "PacketSystem/InputPacket.h"
#include "PacketSystem/ConnectAcceptdPacket.h"
#include "PacketSystem/PacketHeader.h"
#include "PacketSystem/PacketType.h"
#include "UdpSocket.h"
#include <iostream>

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

    int bytes = socket.Receive(
        buffer,
        sizeof(buffer),
        clientAddr);

    if(bytes <= 0)
        return;

    std::cout << "Checando bytes enviados...: " << std::endl;

    PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

    switch(header->type)
    {
        case PacketType::Connect:
            handleConnect(clientAddr);
            break;

        case PacketType::Input:
            handleInput(clientAddr, buffer, bytes);
            break;

        default:
            break;
    }
    
    // interpretar pacote e enviar para algum lugar depois
    socket.Send(buffer, bytes, clientAddr);
}

void GameServer::handleConnect(
    const sockaddr_in& clientAddr)
{
    std::cout << "\n\nHandle Connect: \nCriando conexão para o player" << std::endl;
    Player player;

    player.id = nextPlayerId++; 
    player.transform.x = 0.0f;
    player.transform.y = 0.0f;
    
    world.AddPlayer(player);

    std::cout << "Player adicionado ao mundo" << std::endl;
    PlayerSession session;

    session.playerId = player.id;
    session.endpoint = clientAddr;
    session.connected = true;

    sessionManager.AddSession(session);
     std::cout
        << "Player conectado à uma sessão, ID: "
        << player.id
        << std::endl;

    ConnectAcceptedPacket response;
    response.header.type = PacketType::ConnectAccepted;
    response.playerId = player.id;

    socket.Send(reinterpret_cast<char*>(&response), sizeof(response), clientAddr);
    std::cout << "Conexão aceita\n\n" << std::endl;
}

void GameServer::handleInput(
    const sockaddr_in& clientAddr,
    const char* buffer,
    int bytes)
{
   
}

void GameServer::handleInteract()
{
    
}

void GameServer::handleDisconnect()
{
    
}