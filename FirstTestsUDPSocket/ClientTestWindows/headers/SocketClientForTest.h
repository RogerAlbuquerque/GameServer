#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <string>
class SocketClient {
public:

  bool createSocket();

  void SendConnectPacket(const sockaddr_in &clientAddr);

  void SendCleanInputPacket(const sockaddr_in &clientAddr);
  
  void SendInputButton(const sockaddr_in &clientAddr);

  void receiveThread();

  void HandleConnectAccepted(const char* buffer, int bytes);
  
  void HandleSnapshot(const char* buffer,int bytes);

  sockaddr_in GetAccessForGamerServer();


private:
  SOCKET socketFd = INVALID_SOCKET;

  uint32_t playerId;

};