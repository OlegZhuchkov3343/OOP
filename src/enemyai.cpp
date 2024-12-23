#include "enemyai.h"


void EnemyAI::takeRandomShot(GameField& field) {
    std::vector<Coordinate> possibilities;
    for (int i = 0; i < field.get_rows(); i++){
        for (int j = 0; j < field.get_cols(); j++){
            if (field.checkCell(Coordinate{i, j})){
                possibilities.push_back(Coordinate{i,j});
            }
        }
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, possibilities.size() - 1);
    int random_index = dis(gen);
    field.attackCell(possibilities[random_index]);
    std::cout << "Enemy attacked your cell: " << possibilities[random_index].x << " " << possibilities[random_index].y << std::endl;
}

std::vector<ShipPlacementArgs> EnemyAI::getEnemyShipPlacement(int rows, int cols) {
    // TODO: random ship placement for input size
    return {{4,{0,0},true}, {3,{2,1},false}, {3,{2,3},true}};
}