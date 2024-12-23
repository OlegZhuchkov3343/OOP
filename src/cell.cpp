#include "cell.h"


Cell::Cell() : status(CellStatus::Unknown), ship_segment((ShipSegment*) nullptr) {}

CellStatus Cell::get_status() const {
    return status;
}

ShipSegment* Cell::get_segment() const {
    return ship_segment;
}

void Cell::set_segment(ShipSegment* segment) {
    ship_segment = segment;
}

void Cell::set_status(CellStatus new_status) {
    status = new_status;
}
