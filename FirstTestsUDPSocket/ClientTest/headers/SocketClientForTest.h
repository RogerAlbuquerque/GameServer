#pragma once
#include <arpa/inet.h>

class SocketClient {
public:

  int createSocket();

  void SendConnectPacket(const sockaddr_in &clientAddr);

  void SendInputPacket(const sockaddr_in &clientAddr);

  

  sockaddr_in GetAccessForGamerServer();


private:
  int socketFd = -1;

};