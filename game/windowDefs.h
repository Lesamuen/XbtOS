#ifndef WINDOWDEFS_H
#define WINDOWDEFS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
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
extern std::unordered_map<std::string, SDL_Texture*> images;

// Hash table that maps font textures to their contained text
extern std::unordered_map<std::string, SDL_Texture*> textTextures;

// The main window the game will be using
extern SDL_Window* window;

// The renderer for the window
extern SDL_Renderer* renderer;

// Temporarily, we will be using a single font for the entire app; Roboto Condensed
extern TTF_Font* globalFont;

#endif