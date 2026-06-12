#include "PacketHeader.h"
#include "PlayerSnapshot.h"
struct WorldSnapshotHeader
{
    PacketHeader header;

    uint16_t playerCount;

    // PlayerSnapshot players[32]; // Vetor fixo enquanto é estudo, depois evolui para sistema dinâmico
};