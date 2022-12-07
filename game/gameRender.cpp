#include "gameRender.h"
#include "windowDefs.h"
#include "SDLhelpers.h"
#include "actions.h"

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

    // Put text onto buttons
    SDL_Color white = {255, 255, 255, 255};
    SDL_Texture* text = renderText("Play Card", white);
    int textW, textH;
    SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
    // Multiply by 1.4 for text leading
    textH *= 1.4;

    SDL_Rect fittedSize = fitRect(textW, textH, {0, SCREEN_HEIGHT * 11 / 18, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 18});

    SDL_RenderCopy(renderer, text, NULL, &fittedSize);
    
    // Repeat for others
    text = renderText("Discard", white);
    SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
    textH *= 1.4;
    fittedSize = fitRect(textW, textH, {SCREEN_WIDTH / 6, SCREEN_HEIGHT * 11 / 18, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 18});
    SDL_RenderCopy(renderer, text, NULL, &fittedSize);
    text = renderText("Pass", white);
    SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
    textH *= 1.4;
    fittedSize = fitRect(textW, textH, {SCREEN_WIDTH * 2 / 6, SCREEN_HEIGHT * 11 / 18, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 18});
    SDL_RenderCopy(renderer, text, NULL, &fittedSize);
    text = renderText("Sidestep", white);
    SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
    textH *= 1.4;
    fittedSize = fitRect(textW, textH, {SCREEN_WIDTH * 3 / 6, SCREEN_HEIGHT * 11 / 18, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 18});
    SDL_RenderCopy(renderer, text, NULL, &fittedSize);
    text = renderText("Charge", white);
    SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
    textH *= 1.4;
    fittedSize = fitRect(textW, textH, {SCREEN_WIDTH * 4 / 6, SCREEN_HEIGHT * 11 / 18, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 18});
    SDL_RenderCopy(renderer, text, NULL, &fittedSize);
    text = renderText("Strike", white);
    SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
    textH *= 1.4;
    fittedSize = fitRect(textW, textH, {SCREEN_WIDTH * 5 / 6, SCREEN_HEIGHT * 11 / 18, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 18});
    SDL_RenderCopy(renderer, text, NULL, &fittedSize);

    // Card separators (deck + 7 cards, bottom 3/9)
    for (int i = 0; i < 8; i++) {
        SDL_RenderDrawLine(renderer, SCREEN_WIDTH * i / 8, SCREEN_HEIGHT * 2 / 3, SCREEN_WIDTH * i / 8, SCREEN_HEIGHT);
    }
    SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 8, SCREEN_HEIGHT * 13 / 18, SCREEN_WIDTH, SCREEN_HEIGHT * 13 / 18);

    // Text for deck
    text = renderText("DECK", white);
    SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
    textH *= 1.4;
    fittedSize = fitRect(textW, textH, {0, SCREEN_HEIGHT * 2 / 3, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 18});
    SDL_RenderCopy(renderer, text, NULL, &fittedSize);

    // Reset drawColor to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void renderActions(heroActions& heroActions) {
    SDL_Color white = {255, 255, 255, 255};
    int textW, textH;

    // First, do deck text
    SDL_Texture* text = renderText("Current Actions", white);
    SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
    textH *= 1.4;
    SDL_Rect fittedSize = fitRect(textW, textH, {0, SCREEN_HEIGHT * 14 / 18, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 18});
    SDL_RenderCopy(renderer, text, NULL, &fittedSize);

    text = renderText(std::to_string(heroActions.getCurrentActions()), white);
    SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
    textH *= 1.4;
    fittedSize = fitRect(textW, textH, {0, SCREEN_HEIGHT * 15 / 18, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 18});
    SDL_RenderCopy(renderer, text, NULL, &fittedSize);

    text = renderText("Total Actions", white);
    SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
    textH *= 1.4;
    fittedSize = fitRect(textW, textH, {0, SCREEN_HEIGHT * 16 / 18, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 18});
    SDL_RenderCopy(renderer, text, NULL, &fittedSize);

    text = renderText(std::to_string(heroActions.getTotalActions()), white);
    SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
    textH *= 1.4;
    fittedSize = fitRect(textW, textH, {0, SCREEN_HEIGHT * 17 / 18, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 18});
    SDL_RenderCopy(renderer, text, NULL, &fittedSize);

    // Next, do card text
    for (int i = 0; i < heroActions.getNumHand(); i++) {
        action& action = heroActions.getHandAction(i);
    
        text = renderText(action.name, white);
        SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
        textH *= 1.4;
        fittedSize = fitRect(textW, textH, {SCREEN_WIDTH * (i + 1) / 8, SCREEN_HEIGHT * 12 / 18, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 18});
        SDL_RenderCopy(renderer, text, NULL, &fittedSize);

        text = renderText(action.description, white);
        SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
        textH *= 1.4;
        fittedSize = fitRect(textW, textH, {SCREEN_WIDTH * (i + 1) / 8, SCREEN_HEIGHT * 8 / 9, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 9});
        SDL_RenderCopy(renderer, text, NULL, &fittedSize);
    }
}

void renderSelectedAction(const int& action) {
    if (action == -1) {
        // No action selected
        return;
    } else if (action > -1) {
        SDL_Rect box = {SCREEN_WIDTH * (action + 1) / 8, SCREEN_HEIGHT * 2 / 3, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 3};
        SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255);
        SDL_RenderDrawRect(renderer, &box);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    } else {
        SDL_Rect box = {SCREEN_WIDTH * (action * (-1)) / 6, SCREEN_HEIGHT * 11 / 18, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 18};
        SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255);
        SDL_RenderDrawRect(renderer, &box);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
}