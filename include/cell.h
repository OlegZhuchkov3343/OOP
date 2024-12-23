#ifndef CELL_H
#define CELL_H
#include "shipsegment.h"


enum CellStatus { Unknown, Empty, ShipFound };

class Cell {
private:
    CellStatus status;
    ShipSegment* ship_segment;

public:
    explicit Cell();
    CellStatus get_status() const;
    ShipSegment* get_segment() const;
    void set_status(CellStatus);
    void set_segment(ShipSegment*);
};
#endif