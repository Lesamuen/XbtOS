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

    /* Addition for coordinates, in-place.
     */
    coordinate& operator+=(const coordinate& other);

    /* Return a rotated version of the coordinate, rotated around the origin.
     * Only in 90 degree increments.
     * 
     * Input:
     *      amount = amount of 90 degree increments to rotate clockwise (in terms of screen space) by. Downwards (positive y) is default.
     * 
     * Throws:
     *      0 - amount is not within 0-3.
     */
    coordinate rotation(int amount) const;


    /* Rotated the coordinate in place, around the origin.
     * Only in 90 degree increments.
     * 
     * Input:
     *      amount = amount of 90 degree increments to rotate clockwise (in terms of screen space) by. Downwards (positive y) is default.
     * 
     * Throws:
     *      0 - amount is not within 0-3.
     */
    void rotate(int amount);
};

#endif