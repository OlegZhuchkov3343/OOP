#include "shipsegment.h"


ShipSegment::ShipSegment() : status(SegmentStatus::Intact) {};


SegmentStatus ShipSegment::get_status() const {
    return status;
}

void ShipSegment::takeDamage() {
    if (status == SegmentStatus::Intact)
        status = SegmentStatus::Damaged;
    else if (status == SegmentStatus::Damaged){
        status = SegmentStatus::Destroyed;
        destroyed_recently = true;
    }
}

void ShipSegment::set_status(SegmentStatus status) {
    this->status = status;
}

bool ShipSegment::get_destroyed_recently() const{
    return this->destroyed_recently;
}

void ShipSegment::set_destroyed_recently(bool value){
    this->destroyed_recently = value;
}