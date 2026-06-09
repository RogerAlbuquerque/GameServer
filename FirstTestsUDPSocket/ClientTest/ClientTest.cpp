
#include "headers/ConnectPacket.h"
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "headers/InputPacket.h"
#include "headers/SocketClientForTest.h"

int main()
{
    char tecla;
    SocketClient socket;
    int socketFd = socket.createSocket();
    sockaddr_in GameServerAddr = socket.GetAccessForGamerServer();

    std::cout << "Send one type of packet for server:\n" << std::endl;
    std::cout << "C: ConnectPacket - 01" << std::endl;
    std::cout << "I: InputPacket - 03" << std::endl;

    while (true) {


      std::cin >> tecla;

      switch (tecla) {
            case 'c':
            case 'C':
                socket.SendConnectPacket(GameServerAddr);
                break;

            case 'i':
            case 'I':
                socket.SendInputPacket(GameServerAddr);
                break;
      }
    }

    return 0;
}

int SocketClient::createSocket(){

    socketFd = socket(AF_INET, SOCK_DGRAM, 0);
  if (socketFd < 0)
    return false;

  sockaddr_in localAddr{};
  localAddr.sin_family = AF_INET;
  localAddr.sin_port = htons(50000); // porta fixa
  localAddr.sin_addr.s_addr = INADDR_ANY;

  if(bind(socketFd, (sockaddr *)&localAddr, sizeof(localAddr)))
  {
    std::cout << "Erro ao iniciar o servidor" << std::endl;
    return false;
  }

  return true;
}

sockaddr_in SocketClient::GetAccessForGamerServer(){
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7777);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    return serverAddr;
}



void SocketClient::SendConnectPacket(const sockaddr_in &clientAddr){
  ConnectPacket connect{};
  connect.header.type = PacketType::Connect;

  sendto(socketFd, reinterpret_cast<char *>(&connect), sizeof(connect), 0,
         (sockaddr *)&clientAddr, sizeof(clientAddr));
}

void SocketClient::SendInputPacket(const sockaddr_in &clientAddr){
  InputPacket Input{};
  Input.header.type = PacketType::Input;

  sendto(socketFd, reinterpret_cast<char *>(&Input), sizeof(Input), 0,
         (sockaddr *)&clientAddr, sizeof(clientAddr));
}