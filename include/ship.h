#ifndef SHIP_H
#define SHIP_H
#include <stdexcept>
#include <shipsegment.h>


class Ship {
private:
    int length;
    ShipSegment* segments;
    bool destroyed_recently = false;

public:
    explicit Ship(int length);
    int get_length() const;
    SegmentStatus get_segment_status(int index) const;
    bool is_destroyed() const;
    bool updateDestroyed();
    ShipSegment* get_segment(int index) const;
};
#endif