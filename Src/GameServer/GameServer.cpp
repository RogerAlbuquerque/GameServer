#include "GameServer.h"
#include "Endpoint.h"
#include "PacketSystem/ConnectAcceptdPacket.h"
#include "PacketSystem/InputFlags.h"
#include "PacketSystem/InputPacket.h"
#include "PacketSystem/PacketHeader.h"
#include "PacketSystem/PacketType.h"
#include "PlayerSession.h"
#include "UdpSocket.h"
#include <iostream>
#include <memory>

bool GameServer::Start() { return socket.Start(7777); }

void GameServer::Run() {
  while (true) {
    receivePackets();

    // updateGame();

    // sendSnapshots();
  }
}

void GameServer::receivePackets() {
  char buffer[1024];

  sockaddr_in clientAddr;

  int bytes = socket.Receive(buffer, sizeof(buffer), clientAddr);

  if (bytes <= 0)
    return;

  std::cout << "Checando bytes enviados...: " << std::endl;

  PacketHeader *header = reinterpret_cast<PacketHeader *>(buffer);

  switch (header->type) {
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

void GameServer::handleConnect(const sockaddr_in &clientAddr) {

  std::cout << "\n\nHandle Connect: \nCriando conexão para o player"
            << std::endl;
  Player player;

  player.id = ++nextPlayerId;
  player.transform.x = 0.0f;
  player.transform.y = 0.0f;
  std::cout << "Player criado com sucesso" << std::endl;

  std::cout << "Criando sessão para o player" << std::endl;
  std::unique_ptr<PlayerSession> session = std::make_unique<PlayerSession>();
  session->playerId = player.id;
  session->endpoint = clientAddr;
  session->connected = true;
  sessionManager.AddSession(std::move(session));
  std::cout << "Player conectado à uma sessão, ID: " << player.id << std::endl;

  ConnectAcceptedPacket response;
  response.header.type = PacketType::ConnectAccepted;
  response.playerId = player.id;

  world.AddPlayer(player);
  std::cout << "Player adicionado ao mundo" << std::endl;

  socket.Send(reinterpret_cast<char *>(&response), sizeof(response),
              clientAddr);
  std::cout << "Conexão aceita\n\n" << std::endl;
}


void GameServer::handleInput(const sockaddr_in &clientAddr, const char *buffer, int bytes) {

  std::cout << "Handle Input: Analisando input do player" << std::endl;

  
  Endpoint endpoint;
  endpoint.ip = clientAddr.sin_addr.s_addr;
  endpoint.port = clientAddr.sin_port;

  PlayerSession *session = sessionManager.GetSessionByEndpoint(endpoint);

  if (session == nullptr)
  {
    std::cout <<"Player não identificado\n\n"<< std::endl;

    return;
  }
  std::cout << "Sessão de player identificada, existe no mundo, está conectado" << std::endl;

  Player *player = world.GetPlayer(session->playerId);

  if (player == nullptr){
    std::cout << "Erro ao adicionar player ao mundo" << std::endl;
    return;}
  
std::cout << "Player adicionado ao mundo" << std::endl;
  if (bytes < sizeof(InputPacket)) {
    return;
  }
  const InputPacket* packet = reinterpret_cast<const InputPacket*>(buffer);

  if (packet->inputFlags & InputFlags::Up) {
    std::cout << "Player " << player->id << " apertou W\n\n" << std::endl;
  }
}

void GameServer::handleInteract() {}

void GameServer::handleDisconnect() {}