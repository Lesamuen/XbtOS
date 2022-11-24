#include "defs.h"

const char* TITLE = "Test";

int SCREEN_WIDTH = 800;

int SCREEN_HEIGHT = 600;

SDL_Rect screenRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

int TPS = 60;

const char* IMAGE_PATHS[IMAGE_ID::NUM_IMAGES] = {
    "img/test.bmp",
    "img/test2.bmp"
};