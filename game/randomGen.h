#ifndef RANDOMGEN_H
#define RANDOMGEN_H

#include <random>

/* The default random generator, seeded, to be used by the rest of the program.
 */
extern std::mt19937 randomGen;

/* Uses the random generator to output a number in a given range, inclusive.
 *
 * Input:
 *      min = lowest bound of range, inclusive
 *      max = highest bound of range, inclusive
 * 
 * Output:
 *      a random integer within the given range
 * 
 * Throws:
 *      0 - min > max
 */
int random(int min, int max);

#endif