#ifndef SHIPSEGMENT_H
#define SHIPSEGMENT_H
#include <stdexcept>


class Ship;

enum SegmentStatus { Intact, Damaged, Destroyed };

class ShipSegment {
private:
    SegmentStatus status;
    bool destroyed_recently = false;

public:
    explicit ShipSegment();
    SegmentStatus get_status() const;
    void takeDamage();
    void set_status(SegmentStatus status);
    bool get_destroyed_recently() const;
    void set_destroyed_recently(bool value);
};
#endif