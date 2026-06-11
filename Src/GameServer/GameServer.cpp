#include <iostream>
#include <chrono>
#include <thread>
#include "GameServer.h"
#include "Endpoint.h"
#include "PacketSystem/ConnectAcceptdPacket.h"
#include "PacketSystem/InputFlags.h"
#include "PacketSystem/InputPacket.h"
#include "PacketSystem/PacketHeader.h"
#include "PacketSystem/PacketType.h"
#include "PacketSystem/PacketWriter.h"
#include "PlayerSession.h"
#include "UdpSocket.h"
#include "WorldSnapshot.h"
#include <cstring>

bool GameServer::Start() { 
  return socket.Start(7777);
}

void GameServer::Run() {
using Clock = std::chrono::steady_clock;

constexpr auto TickTime =

    std::chrono::microseconds(16667);


auto nextTick = Clock::now();

while (true)
{
    receivePackets();

    updateGame();

    sendSnapshot();

    nextTick += TickTime;

    std::this_thread::sleep_until(nextTick);
}
}

void GameServer::receivePackets() {
  char buffer[1024];

  sockaddr_in clientAddr;

  int bytes = socket.Receive(buffer, sizeof(buffer), clientAddr);

  if (bytes <= 0)
    return;

  Endpoint endpoint;
  endpoint.ip = clientAddr.sin_addr.s_addr;
  endpoint.port = clientAddr.sin_port;

  std::cout << "Checando bytes enviados...: " << std::endl;

  PacketHeader *header = reinterpret_cast<PacketHeader *>(buffer);

  switch (header->type) {
  case PacketType::Connect:{


    if(PlayerSession *session = sessionManager.GetSessionByEndpoint(endpoint))
    {
      std::cout << "Player ja conectado" << std::endl;
      return;
    }
    handleConnect(clientAddr);
  }
    
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

  world.AddPlayer(player);
  std::cout << "Player adicionado ao mundo" << std::endl;

  ConnectAcceptedPacket response;
  response.header.type = PacketType::ConnectAccepted;
  response.playerId = player.id;


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
  
  Player *player = world.GetPlayer(session->playerId);
  
  std::cout << "Sessão de player identificada, existe no mundo, está conectado" << std::endl;

  if (player == nullptr){
    std::cout << "Erro ao procurar player no mundo" << std::endl;
    return;}

  std::cout << "Player Encontrado no mundo" << std::endl;
  if (bytes < sizeof(InputPacket)) {
    std::cout << "Deu erro aqui, não é um, ou só um Input Packet que ta chegando" << std::endl;
    return;
  }
  const InputPacket* packet = reinterpret_cast<const InputPacket*>(buffer);
  
  std::cout << "enviando input" << std::endl;

  player->input.left = packet->inputFlags & InputFlags::Left;
  player->input.right = packet->inputFlags & InputFlags::Right;
  player->input.up = packet->inputFlags & InputFlags::Up;
  player->input.down = packet->inputFlags & InputFlags::Down;
  player->input.interact = packet->inputFlags & InputFlags::Interact;

  std::cout << player->input.left << " -> input: left" << std::endl;
  std::cout << player->input.right << " -> input: right" << std::endl;
  std::cout << player->input.up << " -> input: up" << std::endl;
  std::cout << player->input.down << " -> input: down" << std::endl;
  std::cout << player->input.interact << " -> input: interact" << std::endl;
  system("clear");
}


void GameServer::updateGame()
{
  const float deltaTime = 1.0f / 60.0f;

  for (auto &[id, player] : world.GetPlayers()) {
    player.Update(deltaTime);
    std::cout << "\n\nPosição X do player: " << player.transform.x << std::endl;
    std::cout << "\n\nPosição Y do player: " << player.transform.y << std::endl;
    
  }
}

void GameServer::sendSnapshot()
{
  PacketWriter packetWriter;
  WorldSnapshotHeader header{};
  header.header.type = PacketType::Snapshot;
  header.playerCount = 0;
  header.playerCount = world.players.size();
  packetWriter.Write(header);

   std::cout << "\n\nNo mundo tem isso de player: " << world.players.size() << std::endl;
   
  for (auto &[id, player] : world.GetPlayers()) {

    PlayerSnapshot snapshot;

    snapshot.playerId = player.id;

    snapshot.x = player.transform.x;

    snapshot.y = player.transform.y;

    packetWriter.Write(snapshot);

    header.playerCount++;

  }
  

  for(auto& [id, session] : sessionManager.GetAllSessions())
{
    socket.Send(
    packetWriter.Data(),
    packetWriter.Size(),
    session->endpoint);
  
    
}
}


void GameServer::handleInteract() {}

void GameServer::handleDisconnect() {}