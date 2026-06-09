
#include "headers/ConnectPacket.h"
#include "headers/InputFlags.h"
#include "headers/InputPacket.h"
#include "headers/SocketClientForTest.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

int main() {
  WSADATA wsaData;

  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    std::cout << "Erro ao iniciar Winsock\n";
    return -1;
  }
  std::string input;
  SocketClient socket;
  bool socketFd = socket.createSocket();
  sockaddr_in GameServerAddr = socket.GetAccessForGamerServer();

  std::cout << "Send one type of packet for server:\n" << std::endl;
  std::cout << "C: ConnectPacket - 01" << std::endl;
  std::cout << "I: InputPacket - 03" << std::endl;
  std::cout << "Ou teclas WASD para andar" << std::endl;

  socket.SendConnectPacket(GameServerAddr);
  socket.SendInputButton(GameServerAddr);
  // while (true) {
  //   std::cin >> input;
  //   if (input[0] == 'p' || input[0] == 'P') {
  //     break;
  //   }
  //   if (input[0] == 'c' || input[0] == 'C') {
  //     socket.SendConnectPacket(GameServerAddr);
  //   }
  //   if (input[0] == 'i' || input[0] == 'I') {
  //     socket.SendCleanInputPacket(GameServerAddr);
  //   }
  //   if (input[0] != 'c' || input[0] != 'i' || input[0] != 'C' ||
  //       input[0] != 'I') {
  //     socket.SendInputButton(GameServerAddr, input);
  //   }
  // }
  closesocket(socketFd);
  WSACleanup();

  return 0;
}

bool SocketClient::createSocket() {

  socketFd = socket(AF_INET, SOCK_DGRAM, 0);
  if (socketFd < 0)
    return false;

  sockaddr_in localAddr{};
  localAddr.sin_family = AF_INET;
  localAddr.sin_port = htons(50000); // porta fixa
  localAddr.sin_addr.s_addr = INADDR_ANY;

  if (bind(socketFd, (sockaddr *)&localAddr, sizeof(localAddr))) {
    std::cout << "Erro ao iniciar o servidor" << std::endl;
    return false;
  }
  return true;
}

sockaddr_in SocketClient::GetAccessForGamerServer() {
  sockaddr_in serverAddr{};
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7777);
  inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

  return serverAddr;
}

void SocketClient::SendConnectPacket(const sockaddr_in &clientAddr) {
  ConnectPacket connect{};
  connect.header.type = PacketType::Connect;

  sendto(socketFd, reinterpret_cast<char *>(&connect), sizeof(connect), 0,
         (sockaddr *)&clientAddr, sizeof(clientAddr));
}

void SocketClient::SendCleanInputPacket(const sockaddr_in &clientAddr) {
  InputPacket Input{};
  Input.header.type = PacketType::Input;

  sendto(socketFd, reinterpret_cast<char *>(&Input), sizeof(Input), 0,
         (sockaddr *)&clientAddr, sizeof(clientAddr));
}

void SocketClient::SendInputButton(const sockaddr_in &clientAddr) {

  while (true) {
    InputPacket Input{};
    Input.header.type = PacketType::Input;

    if (GetAsyncKeyState('W') & 0x8000)
      Input.inputFlags |= InputFlags::Up;
    if (GetAsyncKeyState('w') & 0x8000)
      Input.inputFlags |= InputFlags::Up;

    if (GetAsyncKeyState('S') & 0x8000)
      Input.inputFlags |= InputFlags::Down;
    if (GetAsyncKeyState('s') & 0x8000)
      Input.inputFlags |= InputFlags::Down;

    if (GetAsyncKeyState('A') & 0x8000)
      Input.inputFlags |= InputFlags::Left;
    if (GetAsyncKeyState('a') & 0x8000)
      Input.inputFlags |= InputFlags::Left;

    if (GetAsyncKeyState('D') & 0x8000)
      Input.inputFlags |= InputFlags::Right;
    if (GetAsyncKeyState('D') & 0x8000)
      Input.inputFlags |= InputFlags::Right;

    if (GetAsyncKeyState('E') & 0x8000)
      Input.inputFlags |= InputFlags::Interact;
    if (GetAsyncKeyState('e') & 0x8000)
      Input.inputFlags |= InputFlags::Interact;

    sendto(socketFd, reinterpret_cast<char *>(&Input), sizeof(Input), 0,
           (sockaddr *)&clientAddr, sizeof(clientAddr));
    Sleep(16);
  }

  //  { // for (char c : input) {

  //   switch (c) {
  //   case 'c':
  //   case 'C':
  //     std::cout << "Tecla não mapeada: C" << std::endl;
  //     break;

  //   case 'i':
  //   case 'I':
  //     std::cout << "Tecla não mapeada I" << std::endl;
  //     break;

  //   case 'a':
  //   case 'A':
  //     Input.inputFlags |= InputFlags::Left;
  //     break;

  //   case 'd':
  //   case 'D':
  //     Input.inputFlags |= InputFlags::Right;
  //     break;

  //   case 'w':
  //   case 'W':
  //     Input.inputFlags |= InputFlags::Up;
  //     break;

  //   case 's':
  //   case 'S':
  //     Input.inputFlags |= InputFlags::Down;
  //     break;

  //   case 'e':
  //   case 'E':
  //     Input.inputFlags |= InputFlags::Interact;
  //     break;

  //   default:
  //     std::cout << "Tecla não mapeada" << std::endl;
  //     break;
  //   }
  // }
  // if(tecla == 'a' || tecla == 'A'){Input.inputFlags = InputFlags::Left;}
  // if(tecla == 'd' || tecla == 'D'){Input.inputFlags = InputFlags::Right;}
  // if(tecla == 'w' || tecla == 'W'){Input.inputFlags = InputFlags::Up;}}
  // if(tecla == 's' || tecla == 'S'){Input.inputFlags = InputFlags::Down;}
}