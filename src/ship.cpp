#include "ship.h"


Ship::Ship(int length) : length(length) {
    if (length < 1 || length > 4){
        throw std::invalid_argument("Invalid ship length.");
    }
    segments = (ShipSegment*) malloc(sizeof(ShipSegment)*length);
    for (int i = 0; i < length; i++){
        segments[i] = ShipSegment();
    }
}

int Ship::get_length() const {
    return length;
}

SegmentStatus Ship::get_segment_status(int index) const {
    if (index < 0 || index >= length){
        throw std::out_of_range("Segment index out of range.");
    }
    return segments[index].get_status();
}

bool Ship::is_destroyed() const {
    for (int i = 0; i < length; i++) {
        if (segments[i].get_status() != SegmentStatus::Destroyed) {
            return false;
        }
    }
    return true;
}

bool Ship::updateDestroyed() {
    if (destroyed_recently) destroyed_recently = false;
    if (this->is_destroyed()){
        for (int i = 0; i < length; i++) {
            if (segments[i].get_destroyed_recently()){
                segments[i].set_destroyed_recently(false);
                this->destroyed_recently = true;
            }
        }
    }
    for (int i = 0; i < length; i++) {
        if (segments[i].get_destroyed_recently()){
            segments[i].set_destroyed_recently(false);
        }
    }
    return this->destroyed_recently;
}

ShipSegment* Ship::get_segment(int index) const {
    return segments + index;
}
