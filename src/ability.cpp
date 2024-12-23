#include "ability.h"


void DoubleDamage::Activate(Coordinate target, GameField& field) {
    field.attackCell(target);
    field.attackCell(target);
    std::cout << "Attacked cell: " << target.x << " " << target.y << std::endl;
}

std::string DoubleDamage::name(){
    return "Double Attack";
}

void Scanner::Activate(Coordinate target, GameField& field) {
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++) {
            if (field.checkCell(Coordinate{target.x+i, target.y+j})){
                std::cout << "Ship found in area" << std::endl;
                return;
            }
        }
    }
    std::cout << "No ship found in area" << std::endl;
}

std::string Scanner::name(){
    return "Scanner";
}

void Scattershot::Activate(Coordinate _target, GameField& field) {
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
    std::cout << "Attacked cell: " << possibilities[random_index].x << " " << possibilities[random_index].y << std::endl;
}

std::string Scattershot::name(){
    return "Scattershot";
}