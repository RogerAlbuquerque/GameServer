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
    
    
    // interpretar pacote e enviar para algum lugar depois
    socket.Send(buffer, bytes, clientAddr);
}

