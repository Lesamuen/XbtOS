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

void renderGameScreen() {
    SDL_RenderClear(renderer);

    // 11x11 tile map (from top, centered width, 5.5/9 of height)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < 12; i++) {
        // Horizontal
        SDL_RenderDrawLine(renderer, SCREEN_WIDTH * 21 / 64, SCREEN_HEIGHT * i / 18, SCREEN_WIDTH * 43 / 64, SCREEN_HEIGHT * i / 18);

        // Vertical
        SDL_RenderDrawLine(renderer, SCREEN_WIDTH * (21 + 2 * i) / 64, 0, SCREEN_WIDTH * (21 + 2 * i) / 64, SCREEN_HEIGHT * 11 / 18);
    }

    // Button bar ((5.5 to 6)/9 height)
    SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT * 11 / 18, SCREEN_WIDTH, SCREEN_HEIGHT * 11 / 18);
    SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT * 12 / 18, SCREEN_WIDTH, SCREEN_HEIGHT * 12 / 18);
    // Buttons for: Play card, discard, Pass, Sidestep, Charge, Strike
    for (int i = 0; i < 6; i++) {
        SDL_RenderDrawLine(renderer, SCREEN_WIDTH * i / 6, SCREEN_HEIGHT * 11 / 18, SCREEN_WIDTH * i / 6, SCREEN_HEIGHT * 12 / 18);
    }

    // Card separators (deck + 7 cards, bottom 3/9)
    for (int i = 0; i < 8; i++) {
        SDL_RenderDrawLine(renderer, SCREEN_WIDTH * i / 8, SCREEN_HEIGHT * 2 / 3, SCREEN_WIDTH * i / 8, SCREEN_HEIGHT);
    }

    // Reset drawColor to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}