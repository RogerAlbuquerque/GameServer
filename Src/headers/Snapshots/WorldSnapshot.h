#include "PacketSystem/PacketHeader.h"
#include "PlayerSnapshot.h"
struct WorldSnapshot
{
    PacketHeader header;

    uint16_t playerCount;

    PlayerSnapshot players[32]; // Vetor fixo enquanto é estudo, depois evolui para sistema dinâmico
};