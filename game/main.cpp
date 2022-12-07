#include "windowDefs.h"
#include "SDLhelpers.h"
#include "actions.h"
#include "standardActions.h"
#include "standardEnemies.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

int main (int argc, char** argv) {
    // Attempt to initialize program
    try {
        init();
    } catch (int e) {
        switch (e) {
            case 0:
		        std::cout << "ERROR in SDL video init: " << SDL_GetError() << std::endl;
            break;

            case 1: 
                std::cout << "ERROR in SDL_image PNG system init: " << IMG_GetError() << std::endl;
            break;

            case 2:
		        std::cout << "ERROR in window creation: " << SDL_GetError() << std::endl;
            break;

            case 3:
		        std::cout << "ERROR in renderer creation: " << SDL_GetError() << std::endl;
            break;
        }
		std::cout << "Failed to initialize!\nQuitting...\n";
        return 0;
    }

    // Place images in memory
    loadStandardMedia();

    // Initialize the game Actions
    initStandardActions();

    // Initialize the game Enemies
    initStandardEnemies();

    // Initialize the hero
    heroActions heroActions;



    // Game loop handler
    bool quitFlag = false;
    // Event handler
    SDL_Event event;
    // Test toggle state; switch between test images
    bool test = false;
    // Whether need to update image (only update render when needed, to save resources)
    bool render = false;

    // Main game loop
    while (!quitFlag) {
        // Handle all queued events
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                // Detect if user requests exit the normal way
                case SDL_QUIT:
                    quitFlag = true;
                break;

                // Keyboard inputs
                case SDL_KEYDOWN:
                    std::cout << event.key.keysym.sym << " was pressed." << std::endl;
                    switch (event.key.keysym.sym) {
                        // Toggle image
                        case SDLK_ESCAPE:
                            SDL_RenderClear(renderer);
                            if (test) {
                                SDL_RenderCopy(renderer, images.at("test.bmp"), NULL, NULL);
                                test = false;
                                render = true;
                            } else {
                                SDL_RenderCopy(renderer, images.at("test.png"), NULL, NULL);
                                test = true;
                                render = true;
                            }
                        break;

                        // Testing cards
                        case SDLK_a:
                            std::cout << "Printing hand:" << std::endl;
                            heroActions.printHand();
                        break;

                        case SDLK_s:
                            heroActions.shuffle();
                            std::cout << "Shuffled." << std::endl;
                        break;
                        
                        case SDLK_d:
                            try {
                                heroActions.draw();
                                std::cout << "Drew." << std::endl;
                            } catch (int e) {
                                if (e == 0) {
                                    std::cout << "The deck is empty." << std::endl;
                                } else
                                if (e == 1) {
                                    std::cout << "The hand is full." << std::endl;
                                }
                            }
                        break;
                    }
                break;
            }
        }

        // Render (update surface) if needed
        if (render)
        {
            render = false;
            SDL_RenderPresent(renderer);
        }
        
        // Simulate ticks per second naively
        // TODO: keep track of system time to get true TPS
        SDL_Delay(1000/TPS);
    }

	close(window, images);

	return 0;
}