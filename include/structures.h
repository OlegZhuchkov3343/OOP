#ifndef STRUCTURES_H
#define STRUCTURES_H

struct Coordinate {
    int x;
    int y;
};

struct ShipPlacementArgs {
    int length;
    Coordinate coords;
    bool horizontal;
};
#endif