#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <game.h>

#include <json.hpp>
#include <fstream>

class GameState {
private:
    nlohmann::json to_json();
    nlohmann::json to_json(std::vector<ShipPlacementArgs>);
    nlohmann::json to_json(std::queue<Ability*> abilities);
    nlohmann::json to_json(GameField& field);
    void from_json(nlohmann::json j, ShipManager& player_manager, ShipManager& enemy_manager, AbilityManager& ability_manager);
    void from_json_ships(nlohmann::json j, ShipManager& manager,bool player);
    void from_json_ability(nlohmann::json j, AbilityManager& manager);
    void from_json_field(nlohmann::json j, ShipManager& manager, bool player);
public:
    std::vector<ShipPlacementArgs> player_ships;
    std::vector<ShipPlacementArgs> enemy_ships;
    GameField player_field;
    GameField enemy_field;
    std::queue<Ability*> player_abilities;
    GameState(std::vector<ShipPlacementArgs> player_ships, std::vector<ShipPlacementArgs> enemy_ships, GameField& player_field, GameField& enemy_field, AbilityManager& abilities);
    void serialize();
    void deserialize(ShipManager& player_manager, ShipManager& enemy_manager, AbilityManager& ability_manager);
};

#endif