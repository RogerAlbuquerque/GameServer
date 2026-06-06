#pragma once

#include <arpa/inet.h>

class UdpSocket
{
public:

    bool Start(int port);

    int Receive(
        char* buffer,
        int bufferSize,
        sockaddr_in& clientAddr);

    int Send(
        const char* buffer,
        int size,
        const sockaddr_in& clientAddr);

private:

    int socketFd = -1;
};