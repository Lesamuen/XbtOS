#ifndef WINDOWDEFS_H
#define WINDOWDEFS_H

#include <SDL2\SDL.h>

// Title
extern const char* TITLE;

// X-value of window
extern int SCREEN_WIDTH;

// Y-value of window
extern int SCREEN_HEIGHT;

// SDL Rectangle that represents the size of the screen
extern SDL_Rect screenRect;

// Ticks per second of core game loop
extern int TPS;

// Defs for IDs of images that need to be loaded
enum IMAGE_ID {
    img_test,
    img_test2,
    NUM_IMAGES
};

// Array that maps file paths to IMAGE_ID
extern const char* IMAGE_PATHS[IMAGE_ID::NUM_IMAGES];

#endif