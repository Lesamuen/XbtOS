#include "windowDefs.h"
#include "SDLhelpers.h"
#include "actions.h"
#include "standardActions.h"

#include <iostream>

int main (int argc, char** argv) {
    // Attempt to initialize program
	SDL_Window* window;
    try {
        window = init();
    } catch (int e) {
		std::cout << "Failed to initialize!\nQuitting...\n";
        return 0;
    }
	SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

    // Place images in memory
    std::vector<SDL_Surface*> images = loadAllMedia(screenSurface->format);

    // Initialize the game Actions
    initStandardActions();
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
                            if (test) {
                                SDL_BlitScaled(images[IMAGE_ID::img_test], NULL, screenSurface, &screenRect);
                                test = false;
                                render = true;
                            } else {
                                SDL_BlitScaled(images[IMAGE_ID::img_test2], NULL, screenSurface, &screenRect);
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
                        break;
                        
                        case SDLK_d:
                            try {
                                heroActions.draw();
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
            SDL_UpdateWindowSurface(window);
        }
        
        // Simulate ticks per second naively
        // TODO: keep track of system time to get true TPS
        SDL_Delay(1000/TPS);
    }

	close(window, images);

	return 0;
}