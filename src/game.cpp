#include "game.h"


Game::Game(int field_rows, int field_cols) 
: player_field(GameField(field_rows, field_cols)), enemy_field(GameField(field_rows, field_cols)){};

bool Game::startGame(std::vector<ShipPlacementArgs> player_ships, std::vector<ShipPlacementArgs> enemy_ships) {
    std::cout << "starting game..." << std::endl;
    round = 1;
    ability_used_this_turn = false;
    try {
    placeShips(player_ships, true);
    placeShips(enemy_ships, false);
    } catch (const InvalidShipPlacementException& e) {
        std::cout << e.what() << std::endl;
        return false;
    }
    game_started = true;
    turn = 1;
    player_field.revealField();
    return true;
}

bool Game::shoot(Coordinate target) {
    if (!game_started) return false;
    try{
        enemy_field.attackCell(target);
    }
    catch (const OutOfBoundsException &e){
        std::cout << e.what() << std::endl;
        return false;
    }
    if (enemy_ships.updateRecentlyDestroyedShip())
        player_abilities.gainAbility();
    if (enemy_ships.allDestroyed()) nextRound();
    else enemyTurn();
    return true;
}

bool Game::ability(Coordinate target) {
    if (!game_started) return false;
    if (ability_used_this_turn) return false;
    try {
    player_abilities.useAbility(enemy_field, target);
    } catch (const NoAbilitiesException &e){
        std::cout << e.what() << std::endl;
        return false;
    }
    ability_used_this_turn = true;
    return true;
}

void Game::placeShips(std::vector<ShipPlacementArgs> ships, bool player) {
    for (ShipPlacementArgs args : ships){
        if (player) {
            this->player_ships.newShip(args.length);
            player_field.placeShip(this->player_ships.getShip(), args.coords, args.horizontal);
        }
        else{
            this->enemy_ships.newShip(args.length);
            enemy_field.placeShip(this->enemy_ships.getShip(), args.coords, args.horizontal);
        }
    }
}

void Game::enemyTurn() {
    enemy.takeRandomShot(player_field);
    nextTurn();
}

void Game::nextTurn(){
    ability_used_this_turn = false;
    turn++;
}

void Game::nextRound() {
    std::cout << "Starting new round" << std::endl;
    enemy_field = GameField(enemy_field.get_rows(), enemy_field.get_cols());
    placeShips(enemy.getEnemyShipPlacement(enemy_field.get_rows(), enemy_field.get_cols()), false);
    round++;
    turn = 1;
    ability_used_this_turn = false; 
}

void Game::displayField() {
    std::cout << "Enemy field" << std::endl;
    enemy_field.printField();
    std::cout << "Your field" << std::endl;
    player_field.printField();
}