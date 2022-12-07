#include "windowDefs.h"
#include "SDLhelpers.h"
#include "actions.h"
#include "standardActions.h"
#include "enemy.h"
#include "standardEnemies.h"
#include "gameRender.h"

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

    // Keep track of mouse position
    int mouseX = 0, mouseY = 0;

    // Game loop handler
    bool quitFlag = false;
    // Event handler
    SDL_Event event;
    // Scene handler
    SCENE currentScene = SCENE::title;

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
                    switch (event.key.keysym.sym) {
                        // Another way to exit
                        case SDLK_ESCAPE:
                            quitFlag = true;
                        break;
                    }
                break;

                // Mouse movement
                case SDL_MOUSEMOTION:
                    // Update mouse position
                    SDL_GetMouseState(&mouseX, &mouseY);
                break;

                // Mouse clicks (release)
                case SDL_MOUSEBUTTONUP:
                    switch (event.button.button) {
                        // Left mouse button
                        case SDL_BUTTON_LEFT:

                        break;
                    }
                break;
            }
        }

        if (currentScene == SCENE::title) {
            // Detect if play button selected
            if ((mouseX >= (SCREEN_WIDTH * 5) / 16 && mouseX <= (SCREEN_WIDTH * 11) / 16) && (mouseY >= (SCREEN_HEIGHT * 7) / 9 && mouseY <= (SCREEN_HEIGHT * 8) / 9)) {
                renderTitleScreen(true);
            } else {
                renderTitleScreen(false);
            }
        }

        // Render final frame
        SDL_RenderPresent(renderer);
        
        // Simulate ticks per second naively
        SDL_Delay(1000/TPS);
    }

	close(window, images);

	return 0;
}