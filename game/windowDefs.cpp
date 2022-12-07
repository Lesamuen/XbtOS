#include "windowDefs.h"

const char* TITLE = "X by the One Shot";

int SCREEN_WIDTH = 1600;

int SCREEN_HEIGHT = 900;

SDL_Rect screenRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

int TPS = 30;

std::unordered_map<std::string, SDL_Texture*> images;

std::unordered_map<std::string, SDL_Texture*> textTextures;

SDL_Window* window;

SDL_Renderer* renderer;

TTF_Font* globalFont;