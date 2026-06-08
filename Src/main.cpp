#include "GameServer.h"


int main() {
    
    GameServer server;

    if(!server.Start())
        return -1;

    server.Run();

    return 0;
}