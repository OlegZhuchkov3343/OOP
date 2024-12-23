#include "gamestate.h"


GameState::GameState(std::vector<ShipPlacementArgs> player_ships, std::vector<ShipPlacementArgs> enemy_ships, GameField& player_field, GameField& enemy_field, AbilityManager& abilities)
: player_ships(player_ships), enemy_ships(enemy_ships), player_field(player_field), enemy_field(enemy_field) {
    this->player_abilities = abilities.getAll();
};

nlohmann::json GameState::to_json(){
    nlohmann::json j = {};
    j["player"] = to_json(player_ships);
    j["player"]["field"] = to_json(player_field);
    j["enemy"] = to_json(enemy_ships);
    j["enemy"]["field"] = to_json(enemy_field);
    j["ability"] = to_json(player_abilities);
    return j;
}


nlohmann::json GameState::to_json(std::vector<ShipPlacementArgs> ships){
    nlohmann::json j = {};
    for (ShipPlacementArgs ship : ships){
        nlohmann::json shipj = {};
        shipj["x"] = ship.coords.x;
        shipj["y"] = ship.coords.y;
        shipj["length"] = ship.length;
        shipj["horizontal"] = ship.horizontal;
        j["ships"].push_back(shipj);
    }
    return j;
}

nlohmann::json GameState::to_json(std::queue<Ability*> abilities){
    nlohmann::json j = {};
    while (!abilities.empty()){
        if (abilities.front()->name() == "Double Attack")
            j["abilities"].push_back(0);
        if (abilities.front()->name() == "Scanner")
            j["abilities"].push_back(1);
        if (abilities.front()->name() == "Scattershot")
            j["abilities"].push_back(2);
        abilities.pop();
    }
    return j;
}

nlohmann::json GameState::to_json(GameField& field){
    nlohmann::json j = {};
    Cell** table = field.get_field();
    j["rows"] = field.get_rows();
    j["cols"] = field.get_cols();
    for (int x = 0; x < field.get_rows(); x++)
        for (int y = 0; y < field.get_cols(); y++){
            std::string key = std::to_string(x) + std::to_string(y);
            switch (table[x][y].get_status())
            {
            case CellStatus::Unknown :
                j["table"][key]["state"] = 0;
                break;

            case CellStatus::Empty :
                j["table"][key]["state"] = 1;
                break;
            
            case CellStatus::ShipFound :
                j["table"][key]["state"] = 2;
                break;
            }
            if (field.checkCell({x,y})){
                switch (table[x][y].get_segment()->get_status())
                {
                case SegmentStatus::Intact :
                    j["table"][key]["ship"] = 3;
                    break;
                case SegmentStatus::Damaged :
                    j["table"][key]["ship"] = 2;
                    break;
                case SegmentStatus::Destroyed :
                    j["table"][key]["ship"] = 1;
                    break;
                }
            }
            else{
                j["table"][key]["ship"] = 0;
            }
        }
    return j;
}

void GameState::serialize(){
    nlohmann::json j = to_json();
    std::ofstream file("save.json");
    file << j.dump() << std::endl;
    file.close();
}

void GameState::deserialize(ShipManager& player_manager, ShipManager& enemy_manager, AbilityManager& ability_manager){
    nlohmann::json j;
    std::ifstream file("save.json");
    file >> j;
    file.close();
    from_json(j, player_manager, enemy_manager, ability_manager);
}

void GameState::from_json(nlohmann::json j, ShipManager& player_manager, ShipManager& enemy_manager, AbilityManager& ability_manager){
    from_json_ability(j["ability"], ability_manager);
    from_json_field(j["player"], player_manager, true);
    from_json_field(j["enemy"], enemy_manager, false);
}
void GameState::from_json_ships(nlohmann::json j, ShipManager& manager, bool player){
    for (nlohmann::json ship : j){
        manager.newShip(ship["length"]);
        if (player)
        player_field.placeShip(manager.getShip(), {ship["x"],ship["y"]}, ship["horizontal"]);
        else
        enemy_field.placeShip(manager.getShip(), {ship["x"],ship["y"]}, ship["horizontal"]);
    }
}
void GameState::from_json_ability(nlohmann::json j, AbilityManager& manager){
    if (j.is_null()) return;
    for (int ability : j["abilities"]){
        switch(ability){
            case 0:{
                manager.getAll().push(manager.createAbility(DoubleDamage_));
                break;}
            case 1:{
                manager.getAll().push(manager.createAbility(Scanner_));
                break;}
            case 2:{
                manager.getAll().push(manager.createAbility(Scattershot_));
                break;}
        }
    }
}
void GameState::from_json_field(nlohmann::json j, ShipManager& manager, bool player){
    Cell** table;
    if (player){
        player_field = GameField(j["field"]["rows"], j["field"]["cols"]);
        from_json_ships(j["ships"], manager, player);
        table = player_field.get_field();
    }
    else{
        enemy_field = GameField(j["field"]["rows"], j["field"]["cols"]);
        from_json_ships(j["ships"], manager, player);
        table = enemy_field.get_field();
    }
    for (int x = 0; x < j["field"]["rows"]; x++)
        for (int y = 0; y < j["field"]["cols"]; y++){
            std::string key = std::to_string(x) + std::to_string(y);
            switch ((int) j["field"]["table"][key]["state"])
            {
            case 0:
                table[x][y].set_status(CellStatus::Unknown);
                break;
            case 1:
                table[x][y].set_status(CellStatus::Empty);
                break;
            case 2:
                table[x][y].set_status(CellStatus::ShipFound);
                break;
            }
            switch ((int) j["field"]["table"][key]["ship"])
            {
            case 3 :
                table[x][y].get_segment()->set_status(Intact);
                break;
            case 2 :
                table[x][y].get_segment()->set_status(Damaged);
                break;
            case 1 :
                table[x][y].get_segment()->set_status(Destroyed);
                break;
            case 0 :
                break;
            }
        }
}