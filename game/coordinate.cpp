#include "coordinate.h"

coordinate::coordinate(const int& x, const int& y) : x(x), y(y) {}

coordinate coordinate::operator+(const coordinate& other) {
    return coordinate(this->x + other.x, this->y + other.y);
}

coordinate& coordinate::operator+=(const coordinate& other) {
    x += other.x;
    y += other.y;
    return *this;
}

coordinate coordinate::rotation(int amount) const {
    switch (amount) {
        case 0:
            return *this;
        break;

        case 1:
            // positive y -> negative x, positive x -> positive y
            return coordinate(-y, x);
        break;

        case 2:
            // positive y -> negative y, positive x -> negative x
            return coordinate(-x, -y);
        break;

        case 3:
            // positive y -> positive x, positive x -> negative y
            return coordinate(y, -x);
        break;

        default:
            throw 0;
    }
}

void coordinate::rotate(int amount) {
    switch (amount) {
        case 0:
            return;
        break;

        case 1:
            // positive y -> negative x, positive x -> positive y
            {
            int swapHolder = y;
            y = x;
            x = -swapHolder;
            }
            return;
        break;

        case 2:
            // positive y -> negative y, positive x -> negative x
            y = -y;
            x = -x;
            return;
        break;

        case 3:
            // positive y -> positive x, positive x -> negative y
            {
            int swapHolder = y;
            y = -x;
            x = swapHolder;
            }
            return;
        break;

        default:
            throw 0;
    }
}