#include "SDLhelpers.h"
#include "windowDefs.h"

#include <string>
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

    // Init SDL TTF extension library
    if (TTF_Init() == -1) {
        throw 2;
    }

    // Create Window
    window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        throw 3;
    }

    // Create texture renderer for created window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        throw 4;
    }

    // Load the global font (currently roboto condensed)
    globalFont = TTF_OpenFont("font/RobotoCondensed-Regular.ttf", 72);
    if (globalFont == NULL) {
        throw 5;
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

SDL_Texture* renderText(const std::string& text, const SDL_Color& color) {
    // Test for previous existence
    if (textTextures.find(text) != textTextures.end()) {
        return textTextures.find(text)->second;
    }

    // Create surface, then convert to texture
    SDL_Surface* generatedSurface = TTF_RenderText_Solid(globalFont, text.c_str(), color);

    if (generatedSurface == NULL) {
        throw 0;
    }

    SDL_Texture* generatedTexture = SDL_CreateTextureFromSurface(renderer, generatedSurface);
    SDL_FreeSurface(generatedSurface);

    if (generatedTexture == NULL) {
        throw 1;
    }

    // Place onto global hash table
    textTextures.emplace(text, generatedTexture);

    return generatedTexture;
}

void close () {
    // Close font
    TTF_CloseFont(globalFont);

	// Cleanup images
	for (std::unordered_map<std::string, SDL_Texture*>::iterator i = images.begin(); i != images.end(); i++) {
		SDL_DestroyTexture(i->second);
	}

	// Cleanup text
	for (std::unordered_map<std::string, SDL_Texture*>::iterator i = textTextures.begin(); i != textTextures.end(); i++) {
		SDL_DestroyTexture(i->second);
	}

    // Destroy window
	SDL_DestroyWindow(window);
	
    // End SDL processes
    TTF_Quit();
    IMG_Quit();
	SDL_Quit();
}

SDL_Rect fitRect(const int& width, const int& height, const SDL_Rect& bound) {
    // Use size ratio to fit to a box and keep proportions
    double sizeRatio = (double) width / height;
    double boundRatio = ((double) bound.w) / ((double) bound.h);

    // Test whether to fit to height or length
    SDL_Rect fittedSize;
    if (sizeRatio > boundRatio) {
        // Fit to width
        fittedSize.x = bound.x;
        fittedSize.w = bound.w;
        fittedSize.h = bound.w / sizeRatio;
        fittedSize.y = bound.y + (bound.h / 2.0) - (fittedSize.h / 2.0);
    } else {
        // Fit to height
        fittedSize.y = bound.y;
        fittedSize.h = bound.h;
        fittedSize.w = bound.h * sizeRatio;
        fittedSize.x = bound.x + (bound.w / 2.0) - (fittedSize.w / 2.0);
    }

    return fittedSize;
}

bool inBounds(const int& testX, const int& testY, const SDL_Rect& bound) {
    return (testX >= bound.x && testX <= bound.x + bound.w) && (testY >= bound.y && testY <= bound.y + bound.h);
}