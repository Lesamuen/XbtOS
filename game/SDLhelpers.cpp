#include "SDLhelpers.h"
#include "defs.h"

#include <cstdio>

SDL_Window* init() {
	// Init SDL graphics subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("ERROR in SDL video init: %s\n", SDL_GetError());
        throw 0;
	}

    // Create Window
    SDL_Window* window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("ERROR in SDL window creation: %s\n", SDL_GetError());
        throw 1;
    }

    return window;
}

SDL_Surface* loadMedia(const char*& path) {
	// Load image
    SDL_Surface* image = SDL_LoadBMP(path);
	if (image == NULL) {
		throw 0;
	}
    return image;
}

std::vector<SDL_Surface*> loadAllMedia(SDL_PixelFormat*& format) {
    std::vector<SDL_Surface*> images;

    // Load each image sequentially based on IMAGE_PATHS in defs.cpp.
	for (int i = 0; i < IMAGE_ID::NUM_IMAGES; i++) {
        try {
            SDL_Surface* rawImage = loadMedia(IMAGE_PATHS[i]);

            // Convert to given format
            SDL_Surface* convImage = SDL_ConvertSurface(rawImage, format, 0);
            if (convImage == NULL) {
                printf("ERROR in converting image %i: %s\n", i, SDL_GetError());
                // Load default image
                images.push_back(NULL);
            } else {
                images.push_back(convImage);
            }

            // Cleanup previous unprocessed version
            SDL_FreeSurface(rawImage);
        } catch (int e) {
		    printf("ERROR in loading image %i: %s\n", i, SDL_GetError());
            // Load default image
            images.push_back(NULL);
        } 
	}

    return images;
}

void close (SDL_Window*& window, std::vector<SDL_Surface*>& images) {
	// Cleanup
	for (int i = 0; i < images.size(); i++)
	{
		SDL_FreeSurface(images[i]);
	}
	images.clear();
	SDL_DestroyWindow(window);
	
	SDL_Quit();
}