#include "SDLhelpers.h"
#include "windowDefs.h"

#include <iostream>
#include <fstream>

SDL_Window* init() {
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
    SDL_Window* window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        throw 2;
    }

    return window;
}

void loadMedia(const std::string& path, SDL_PixelFormat*& format) {
	// Try to load image
    SDL_Surface* rawImage = IMG_Load(("img/" + path).c_str());
	if (rawImage == NULL) {
		throw 0;
	}
    
    // Try to convert image
    SDL_Surface* convertedImage = SDL_ConvertSurface(rawImage, format, 0);
    SDL_FreeSurface(rawImage);
    if (convertedImage == NULL) {
        throw 1;
    }

    // Place onto hash table in specific format (will just be null if unable to load)
    images.emplace(path, convertedImage);
}

void loadStandardMedia(SDL_PixelFormat*& format) {
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
            loadMedia(path, format);
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

void close (SDL_Window*& window, std::unordered_map<std::string, SDL_Surface*>& images) {
	// Cleanup images
	for (std::unordered_map<std::string, SDL_Surface*>::iterator i = images.begin(); i != images.end(); i++) {
		SDL_FreeSurface(i->second);
	}

    // Destroy window
	SDL_DestroyWindow(window);
	
    // End SDL processes
    IMG_Quit();
	SDL_Quit();
}