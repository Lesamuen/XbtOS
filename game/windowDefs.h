#ifndef WINDOWDEFS_H
#define WINDOWDEFS_H

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>

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

// Hash table that maps images to their path string
extern std::unordered_map<std::string, SDL_Surface*> images;

#endif