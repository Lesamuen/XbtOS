#include "randomGen.h"

std::mt19937 randomGen = std::mt19937(std::random_device()());

int random(int min, int max) {
    if (min > max) {
        throw 0;
    }
    return std::uniform_int_distribution<int>(min, max)(randomGen);
}