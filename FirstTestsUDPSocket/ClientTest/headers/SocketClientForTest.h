#pragma once
#include <arpa/inet.h>
#include <string>
class SocketClient {
public:

  int createSocket();

  void SendConnectPacket(const sockaddr_in &clientAddr);

  void SendCleanInputPacket(const sockaddr_in &clientAddr);
  
  void SendInputButton(const sockaddr_in &clientAddr, std::string input);

  

  sockaddr_in GetAccessForGamerServer();


private:
  int socketFd = -1;

};