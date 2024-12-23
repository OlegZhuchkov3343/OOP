#include "game.h"

int main() {

    Game battleship(10,10);

    std::vector<ShipPlacementArgs> player_ships = {{4, {2,2}, true}};
    std::vector<ShipPlacementArgs> enemy_ships = {{4, {0,0}, false}};

    if (battleship.startGame(player_ships, enemy_ships))
        std::cout << "start success" << std::endl;

    battleship.displayField();

    if (battleship.ability({2,0}))
        std::cout << "ability success" << std::endl;

    if (battleship.shoot({0,0}))
        std::cout << "shoot success" << std::endl;

    battleship.displayField();
    battleship.nextRound();
    battleship.displayField();
    return 0;
}
