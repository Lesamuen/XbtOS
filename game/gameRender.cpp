#include "gameRender.h"
#include "windowDefs.h"

#include <SDL2/SDL.h>

void renderTitleScreen(bool playSelected) {
    // Title is up to about 6/9 of height; play button should be 7/9 to 8/9
    // Play button 6/16 in length
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, images.at("TitleScreen.png"), NULL, NULL);

    SDL_Rect playButtonLocation;
    playButtonLocation.x = (SCREEN_WIDTH * 5) / 16;
    playButtonLocation.y = (SCREEN_HEIGHT * 7) / 9;
    playButtonLocation.w = (SCREEN_WIDTH * 6) / 16;
    playButtonLocation.h = SCREEN_HEIGHT / 9;
    // Decide which play button to draw
    if (playSelected) {
        SDL_RenderCopy(renderer, images.at("PlayButtonSelected.png"), NULL, &playButtonLocation);
    } else {
        SDL_RenderCopy(renderer, images.at("PlayButton.png"), NULL, &playButtonLocation);
    }
}