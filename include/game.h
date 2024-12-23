#ifndef GAME_H
#define GAME_H
#include "exceptions.h"
#include "gamefield.h"
#include "shipmanager.h"
#include "abilitymanager.h"
#include "enemyai.h"
#include "gamestate.h"



class Game{
private:
    int field_rows;
    int field_cols;
    GameField player_field;
    GameField enemy_field;
    std::vector<ShipPlacementArgs> pshipargs;
    std::vector<ShipPlacementArgs> eshipargs;
    ShipManager player_ships;
    ShipManager enemy_ships;
    AbilityManager player_abilities;
    EnemyAI enemy;
    bool ability_used_this_turn = false;
    bool game_started = false;
    int round = 1;
    int turn = 1;
public:
    explicit Game(int field_rows, int field_cols);
    bool startGame(std::vector<ShipPlacementArgs> player_ships, std::vector<ShipPlacementArgs> enemy_ships);
    bool shoot(Coordinate target);
    bool ability(Coordinate target = {-1, -1});
    void placeShips(std::vector<ShipPlacementArgs> ships, bool player);
    void enemyTurn();
    void nextTurn();
    void nextRound();
    void displayField();
    void save();
    void load();
};
#endif