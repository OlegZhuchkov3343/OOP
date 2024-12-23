#include "shipmanager.h"

ShipManager::ShipManager(std::vector<int> sizes) {
    for (int length : sizes) {
        newShip(length);
    }
};

void ShipManager::newShip(int length) {
    ships.emplace_back(length);
}

Ship& ShipManager::getShip(int index) {
    if (index == -1) index = ships.size() - 1;
    if (index < 0 || index >= ships.size()) {
        throw std::out_of_range("Ship index out of range.");
    }
    return ships[index];
}

bool ShipManager::updateRecentlyDestroyedShip() {
    bool recently_destroyed = false;
    for (Ship& ship : ships){
        if (ship.is_destroyed() && ship.updateDestroyed()){
            recently_destroyed = true;
        }
    }
    return recently_destroyed;
}

bool ShipManager::allDestroyed(){
    for (Ship& ship : ships){
        if (!ship.is_destroyed())
            return false;
    }
    return true;
}