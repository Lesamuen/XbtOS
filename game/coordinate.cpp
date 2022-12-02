#include "coordinate.h"

coordinate::coordinate(const int& x, const int& y) : x(x), y(y) {}

coordinate coordinate::operator+(const coordinate& other) {
    return coordinate(this->x + other.x, this->y + other.y);
}

coordinate coordinate::operator-(const coordinate& other) {
    return coordinate(this->x - other.x, this->y - other.y);
}