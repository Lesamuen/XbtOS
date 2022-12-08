#include "gameRender.h"
#include "windowDefs.h"
#include "SDLhelpers.h"
#include "actions.h"

#include <SDL2/SDL.h>
#include <math.h>

void renderTitleScreen(const bool& playSelected) {
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

    SDL_Rect fittedSize = fitRect(textW, textH, {0, SCREEN_HEIGHT * 11 / 18, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 18});

    SDL_RenderCopy(renderer, text, NULL, &fittedSize);
    
    // Repeat for others
    text = renderText("Discard", white);
    SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
    fittedSize = fitRect(textW, textH, {SCREEN_WIDTH / 6, SCREEN_HEIGHT * 11 / 18, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 18});
    SDL_RenderCopy(renderer, text, NULL, &fittedSize);
    text = renderText("Pass", white);
    SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
    fittedSize = fitRect(textW, textH, {SCREEN_WIDTH * 2 / 6, SCREEN_HEIGHT * 11 / 18, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 18});
    SDL_RenderCopy(renderer, text, NULL, &fittedSize);
    text = renderText("Sidestep", white);
    SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
    fittedSize = fitRect(textW, textH, {SCREEN_WIDTH * 3 / 6, SCREEN_HEIGHT * 11 / 18, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 18});
    SDL_RenderCopy(renderer, text, NULL, &fittedSize);
    text = renderText("Charge", white);
    SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
    fittedSize = fitRect(textW, textH, {SCREEN_WIDTH * 4 / 6, SCREEN_HEIGHT * 11 / 18, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 18});
    SDL_RenderCopy(renderer, text, NULL, &fittedSize);
    text = renderText("Strike", white);
    SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
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
    SDL_Rect fittedSize = fitRect(textW, textH, {0, SCREEN_HEIGHT * 14 / 18, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 18});
    SDL_RenderCopy(renderer, text, NULL, &fittedSize);

    text = renderText(std::to_string(heroActions.getCurrentActions()), white);
    SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
    fittedSize = fitRect(textW, textH, {0, SCREEN_HEIGHT * 15 / 18, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 18});
    SDL_RenderCopy(renderer, text, NULL, &fittedSize);

    text = renderText("Total Actions", white);
    SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
    fittedSize = fitRect(textW, textH, {0, SCREEN_HEIGHT * 16 / 18, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 18});
    SDL_RenderCopy(renderer, text, NULL, &fittedSize);

    text = renderText(std::to_string(heroActions.getTotalActions()), white);
    SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
    fittedSize = fitRect(textW, textH, {0, SCREEN_HEIGHT * 17 / 18, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 18});
    SDL_RenderCopy(renderer, text, NULL, &fittedSize);

    // Next, do card text
    for (int i = 0; i < heroActions.getNumHand(); i++) {
        action& action = heroActions.getHandAction(i);
    
        text = renderText(action.name, white);
        SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
        fittedSize = fitRect(textW, textH, {SCREEN_WIDTH * (i + 1) / 8, SCREEN_HEIGHT * 12 / 18, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 18});
        SDL_RenderCopy(renderer, text, NULL, &fittedSize);

        text = renderText(action.description, white);
        SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
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

void renderHero(const double& chargeAmount) {
    // Hero icon at 0,0
    SDL_Color heroColor = {255, 215, 0, 255};
    SDL_Texture* text = renderText("HERO", heroColor);
    
    int textW, textH;
    SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
    SDL_Rect fittedSize = fitRect(textW, textH, {SCREEN_WIDTH * 31 / 64, SCREEN_HEIGHT * 5 / 18, SCREEN_WIDTH / 32, SCREEN_HEIGHT / 18});
    SDL_RenderCopy(renderer, text, NULL, &fittedSize);

    // Charge bar
    SDL_Rect chargeBar = {0, (int) ((1.0 - chargeAmount) * 660), 30, (int) (chargeAmount * 660)};
    SDL_Rect chargeBarLocation = {SCREEN_WIDTH * 63 / 64, (int) ((1.0 - chargeAmount) * (SCREEN_HEIGHT * 11 / 18)), SCREEN_WIDTH / 64, (int) (chargeAmount * (SCREEN_HEIGHT * 11 / 18))};
    SDL_RenderCopy(renderer, images.at("ChargeBar.png"), &chargeBar, &chargeBarLocation);
}

void renderEnemy(const coordinate& enemyPosition, const std::string& enemyName) {
    // First test if enemy even needs to be rendered; if off-grid, render an arrow pointing to it instead
    if (enemyPosition.x < -5 || enemyPosition.x > 5 || enemyPosition.y < -5 || enemyPosition.y > 5) {
        // Get point on border that is directly on line between enemy and hero
        // Get sides that line is intersecting to determine what to project onto
        double angle = std::atan2(enemyPosition.y, enemyPosition.x) * 180 / M_PI;

        // pixel values of center of grid
        coordinate heroPixel = {(SCREEN_WIDTH / 2), (SCREEN_HEIGHT * 11 / 36)};
        // pixel values of enemy, relative to center of grid
        coordinate enemyPixel = {(SCREEN_WIDTH * enemyPosition.x / 32), (SCREEN_HEIGHT * enemyPosition.y / 18)};

        // If projecting onto horizontal line, then solve for y
        // If projecting onto vertical line, then solve for x
        coordinate borderPixel = {0, 0};
        if (angle >= 45 && angle < 135) {
            // Bottom border
            borderPixel.y = SCREEN_HEIGHT * 11 / 36;
            borderPixel.x = ((double) enemyPixel.x / enemyPixel.y) * borderPixel.y;
        } else if (angle >= -135 && angle < -45) {
            // Top border
            borderPixel.y = -SCREEN_HEIGHT * 11 / 36;
            borderPixel.x = ((double) enemyPixel.x / enemyPixel.y) * borderPixel.y;
        } else if (angle >= -45 && angle < 45) {
            // Right border
            borderPixel.x = SCREEN_WIDTH * 11 / 64;
            borderPixel.y = ((double) enemyPixel.y / enemyPixel.x) * borderPixel.x;
        } else {
            // Left border
            borderPixel.x = -SCREEN_WIDTH * 11 / 64;
            borderPixel.y = ((double) enemyPixel.y / enemyPixel.x) * borderPixel.x;
        }

        // Set angle in terms of rotation amount clockwise; by default, arrow sprite is pointing upwards, towards negative y or -90 degrees
        angle += 90;
        if (angle < 0) {
            angle += 360;
        }

        // Arrow size is same as tile (.5/16 x .5/9); tip placed on point (-.5/16/2, 0).
        SDL_Rect arrowLocation = {heroPixel.x + borderPixel.x - SCREEN_WIDTH / 64, heroPixel.y + borderPixel.y, SCREEN_WIDTH / 32, SCREEN_HEIGHT / 18};
        SDL_Point arrowTip = {SCREEN_WIDTH / 64, 0};
        SDL_RenderCopyEx(renderer, images.at("EnemyPointer.png"), NULL, &arrowLocation, angle, &arrowTip, SDL_FLIP_NONE);
    } else {
        // Just render enemy name on location
        SDL_Color enemyColor = {142, 0, 0, 255};
        SDL_Texture* text = renderText(enemyName, enemyColor);
        
        int textW, textH;
        SDL_QueryTexture(text, NULL, NULL, &textW, &textH);
        SDL_Rect fittedSize = fitRect(textW, textH, {SCREEN_WIDTH * (31 + enemyPosition.x * 2) / 64, SCREEN_HEIGHT * (5 + enemyPosition.y) / 18, SCREEN_WIDTH / 32, SCREEN_HEIGHT / 18});
        SDL_RenderCopy(renderer, text, NULL, &fittedSize);
    }
}

void renderThreatenedTiles(const std::vector<threatenedTile>& currentThreatened) {
    // Transparent red
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100);
    for (int i = 0; i < (int) currentThreatened.size(); i++) {
        const threatenedTile& tile = currentThreatened.at(i);
        SDL_Rect tileBox = {SCREEN_WIDTH * (31 + 2 * tile.x) / 64, SCREEN_HEIGHT * (5 + tile.y) / 18, SCREEN_WIDTH / 32, SCREEN_HEIGHT / 18};
        SDL_RenderFillRect(renderer, &tileBox);
    }

    // Return to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void renderMovementTiles(const std::vector<coordinate>& movement, const coordinate& selected, const coordinate& enemyPosition) {
    // Transparent green
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 50);

    // Show available tiles to move to
    for (int i = 0; i < (int) movement.size(); i++) {
        const coordinate& tile = movement.at(i);
        // Not valid if on enemy
        if (tile.x == enemyPosition.x && tile.y == enemyPosition.y) {
            continue;
        }
        SDL_Rect tileBox = {SCREEN_WIDTH * (31 + 2 * tile.x) / 64, SCREEN_HEIGHT * (5 + tile.y) / 18, SCREEN_WIDTH / 32, SCREEN_HEIGHT / 18};
        SDL_RenderFillRect(renderer, &tileBox);
    }

    // Gold
    SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255);

    // Box around selected movement tile
    if (selected.x != 0 || selected.y != 0) {
        SDL_Rect tileBox = {SCREEN_WIDTH * (31 + 2 * selected.x) / 64, SCREEN_HEIGHT * (5 + selected.y) / 18, SCREEN_WIDTH / 32, SCREEN_HEIGHT / 18};
        SDL_RenderDrawRect(renderer, &tileBox);
    }

    // Return to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void renderThreatenedHover(const coordinate& mousePos, const DAMAGE_TYPE& damageType) {
    // Consider hover text to be 1/2 height of bar buttons
    // Offset by 10, 10 pixels for mouse cursor
    // Color to contrast everything else
    SDL_Color gold = {255, 215, 0, 255};
    SDL_Texture* text;
    switch (damageType) {
        case DAMAGE_TYPE::physical:
            text = renderText("Physical", gold);
        break;

        case DAMAGE_TYPE::chemical:
            text = renderText("Chemical", gold);
        break;

        case DAMAGE_TYPE::arcane:
            text = renderText("Arcane", gold);
        break;
        
        case DAMAGE_TYPE::flame:
            text = renderText("Flame", gold);
        break;

        case DAMAGE_TYPE::ice:
            text = renderText("Ice", gold);
        break;

        case DAMAGE_TYPE::mind:
            text = renderText("Mind", gold);
        break;
    }

    int textW, textH;
    SDL_QueryTexture(text, NULL, NULL, &textW, &textH);

    double sizeRatio = (double) (SCREEN_HEIGHT / 36) / textH;
    SDL_Rect textLocation = {mousePos.x + 10, mousePos.y + 10, (int) (sizeRatio * textW), SCREEN_HEIGHT / 36};
    SDL_RenderCopy(renderer, text, NULL, &textLocation);
}

void renderGameOverScreen(const bool& playAgainSelected) {
    // Similar to title screen
    // Text is up to about 6/9 of height; play button should be 7/9 to 8/9
    // Play button 6/16 in length
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, images.at("GameOverScreen.png"), NULL, NULL);

    SDL_Rect playButtonLocation = {(SCREEN_WIDTH * 5) / 16, (SCREEN_HEIGHT * 7) / 9, (SCREEN_WIDTH * 6) / 16, SCREEN_HEIGHT / 9};
    // Decide which play button to draw
    if (playAgainSelected) {
        SDL_RenderCopy(renderer, images.at("PlayAgainButtonSelected.png"), NULL, &playButtonLocation);
    } else {
        SDL_RenderCopy(renderer, images.at("PlayAgainButton.png"), NULL, &playButtonLocation);
    }
}