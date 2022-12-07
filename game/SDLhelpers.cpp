#include "SDLhelpers.h"
#include "windowDefs.h"

#include <iostream>
#include <fstream>

void init() {
	// Init SDL graphics subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw 0;
	}

    // Init SDL Image extension library
    // Only using PNG capability at the moment
    if (!(IMG_Init(IMG_INIT_PNG) & (IMG_INIT_PNG))) {
        throw 1;
    }

    // Create Window
    window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        throw 2;
    }

    // Create texture renderer for created window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        throw 3;
    }

    // Set default renderer fill color (black)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Enable alpha blending
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

void loadMedia(const std::string& path) {
    // Try to load image
    SDL_Texture* loadedImage = IMG_LoadTexture(renderer, ("img/" + path).c_str());

    // Place onto hash table in specific format (will just be null if unable to load)
    images.emplace(path, loadedImage);

    if (loadedImage == NULL) {
        throw 0;
    }

    // Place onto hash table in specific format (will just be null if unable to load)
    images.emplace(path, loadedImage);
}

void loadStandardMedia() {
    // Load each image based on a list in external file img/imagePaths.txt
    // Try to get list
    std::ifstream pathList("img/imagePaths.txt");
    if (!pathList.is_open()) {
        throw 0;
    }

    std::string path;
    while (!pathList.eof()) {
        std::getline(pathList, path);
        try {
            loadMedia(path);
            std::cout << "Successfully loaded image " << path << std::endl;
        } catch (int e) {
            if (e == 0) {
                std::cout << "ERROR in obtaining image " << path << ": " << SDL_GetError() << std::endl;
            } else if (e == 1) {
                std::cout << "ERROR in converting image " << path << ": " << SDL_GetError() << std::endl;
            }
        }
    }

    pathList.close();
}

void close (SDL_Window*& window, std::unordered_map<std::string, SDL_Texture*>& images) {
	// Cleanup images
	for (std::unordered_map<std::string, SDL_Texture*>::iterator i = images.begin(); i != images.end(); i++) {
		SDL_DestroyTexture(i->second);
	}

    // Destroy window
	SDL_DestroyWindow(window);
	
    // End SDL processes
    IMG_Quit();
	SDL_Quit();
}