#ifndef SHIPMANAGER_H
#define SHIPMANAGER_H
#include <vector>
#include <stdexcept>
#include "ship.h"


class ShipManager {
private:
    std::vector<Ship> ships;

public:
    ShipManager() {};
    explicit ShipManager(std::vector<int> sizes);
    void newShip(int length);
    Ship& getShip(int index = -1);
    bool updateRecentlyDestroyedShip();
    bool allDestroyed();
};
#endif