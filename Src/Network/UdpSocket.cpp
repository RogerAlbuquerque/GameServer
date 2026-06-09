#include <iostream>
#include <ostream>
#include <unistd.h>
#include "UdpSocket.h"

bool UdpSocket::Start(int port)
{
    socketFd = socket(AF_INET, SOCK_DGRAM, 0);

    if(socketFd < 0)
        return false;

    sockaddr_in serverAddr{};

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if(bind(socketFd,(sockaddr*)&serverAddr,sizeof(serverAddr)) < 0)
    {
        std::cout << "Erro ao iniciar o servidor" << std::endl;
        return false;
    }

    std::cout << "Socket rodando na porta 7777" << std::endl;
    return true;
}


int UdpSocket::Receive(
    char* buffer,
    int bufferSize,
    sockaddr_in& clientAddr)
{
    socklen_t clientSize =
        sizeof(clientAddr);

    std::cout << "\n\nEnvie algum pacote em bytes para se conectar...: " << std::endl;
    return recvfrom(
        socketFd,
        buffer,
        bufferSize,
        0,
        (sockaddr*)&clientAddr,
        &clientSize);
}


int UdpSocket::Send(const char* buffer,int size,const sockaddr_in& clientAddr)
{
    return sendto(
        socketFd,
        buffer,
        size,
        0,
        (sockaddr*)&clientAddr,
        sizeof(clientAddr));
}