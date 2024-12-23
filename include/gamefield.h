#ifndef GAMEFIELD_H
#define GAMEFIELD_H
#include <stdexcept>
#include <iostream>
#include "structures.h"
#include "ship.h"
#include "cell.h"
#include "exceptions.h"


class GameField {
private:
    int rows;
    int cols;
    Cell** field;
    void init_field();
    void swap(GameField& other);
    void deepCopy(const GameField& other);

public:
    GameField(int rows, int cols);
    void placeShip(Ship &ship, Coordinate coords, bool isHorizontal);
    void attackCell(Coordinate coords);
    void printField() const;
    void revealField();
    bool checkCell(Coordinate target) const;
    bool checkAdjacentCells(Coordinate target) const;
    bool validCoords(Coordinate coords) const;
    int get_rows() const;
    int get_cols() const;
    GameField(const GameField& other);
    GameField& operator=(const GameField& other);
    GameField(GameField&& other);
    GameField& operator=(GameField&& other);
};

#endif