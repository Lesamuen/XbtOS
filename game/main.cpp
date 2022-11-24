#include "defs.h"
#include "SDLhelpers.h"

#include <cstdio>

int main (int argc, char** argv) {
    // Attempt to initialize program
	SDL_Window* window;
    try {
        window = init();
    } catch (int e) {
		printf("Failed to initialize!\nQuitting...\n");
        return 0;
    }
	SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

    // Place images in memory
    std::vector<SDL_Surface*> images = loadAllMedia(screenSurface->format);

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