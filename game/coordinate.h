#ifndef COORDINATE_H
#define COORDINATE_H

/* Simple structure describing a 2D set of Cartesian coordinates, whether relative or absolute.
 * Player character is assumed to be in the center of the grid at (0,0).
 * Bottom right is first quadrant (positive, positive)
 */
struct coordinate {
    int x, y;

    /* Per-parameter constructor.
     */
    coordinate(const int& x, const int& y);

    /* Addition for coordinates.
     */
    coordinate operator+(const coordinate& other);

    /* Subtraction for coordinates.
     */
    coordinate operator-(const coordinate& other);
};

#endif