#include <iostream>
#include "World/World.h"


int main() {
    World world;
    Npc merchant;
    Player player;

    merchant.id = 1;
    merchant.name = "Merhant";
    
    merchant.transform.x = 10;
    merchant.transform.y = 5;

    merchant.interactionRange = 2.0f;

    player.id = 1;

    player.transform.x = 0;
    player.transform.y = 0;

    world.AddPlayer(player);
    world.AddNpc(merchant);

    // Criar player session

    if(world.players.empty())
    {
        std::cout << "World player ta vazio" << std::endl;
    }else{
        std::cout << "Tem player" << std::endl;
    }

     if(world.npcs.empty())
    {
        std::cout << "World player ta vazio" << std::endl;
    }else{
        std::cout << "Tem player" << std::endl;
    }

    return 0;
}