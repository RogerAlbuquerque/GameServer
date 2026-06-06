#include "GameServer.h"


int main() {

    GameServer server;

    if(!server.Start())
        return -1;

    server.Run();

    return 0;
}




//     World world;
//     PlayerSession playerSession;
//     SessionManager sessionManager;
//     Npc merchant;
//     Player player;

//     merchant.id = 1;
//     merchant.name = "Merchant";
//     merchant.transform.x = 10;
//     merchant.transform.y = 5;
//     merchant.interactionRange = 2.0f;

//     player.id = 1;
//     player.transform.x = 0;
//     player.transform.y = 0;

//     world.AddNpc(merchant);
//     world.AddPlayer(player);

// // Instanciar player session
//     playerSession.playerId = player.id;
//     // playerSession.endpoint = clientAdress
//     playerSession.connected = true;
//     playerSession.lastPacketTime = get_current_time_seconds();


    
// // Instanciar Session Manager
//     sessionManager.AddSession(playerSession);

//     if(world.players.empty())
//     {
//         std::cout << "World player ta vazio" << std::endl;
//     }else{
//         std::cout << "Tem player" << std::endl;
//     }

//      if(world.npcs.empty())
//     {
//         std::cout << "World player ta vazio" << std::endl;
//     }else{
//         std::cout << "Tem player" << std::endl;
//     }

//     return 0;
// }