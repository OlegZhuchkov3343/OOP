#ifndef ENEMYAI_H
#define ENEMYAI_H
#include <random>
#include <vector>
#include "gamefield.h"


class EnemyAI {
public:
    void takeRandomShot(GameField& field);
    std::vector<ShipPlacementArgs> getEnemyShipPlacement(int rows, int cols);
};
#endif