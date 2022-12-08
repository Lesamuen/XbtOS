#include "windowDefs.h"
#include "SDLhelpers.h"
#include "actions.h"
#include "standardActions.h"
#include "enemy.h"
#include "standardEnemies.h"
#include "gameRender.h"
#include "randomGen.h"

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
		        std::cout << "ERROR in SDL_TTF system init: " << TTF_GetError() << std::endl;
            break;

            case 3:
		        std::cout << "ERROR in window creation: " << SDL_GetError() << std::endl;
            break;

            case 4:
		        std::cout << "ERROR in renderer creation: " << SDL_GetError() << std::endl;
            break;

            case 5:
		        std::cout << "ERROR in font obtaining: " << TTF_GetError() << std::endl;
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

    // Keep track of current enemy
    std::string currentEnemy = "NULL";
    coordinate enemyPosition = {0, 0};
    moveGroup currentMoves;
    int* currentMove;
    // Keep track of current threatened tiles on the grid
    std::vector<threatenedTile> currentThreatened;

    // Keep track of remaining "time" in ticks in enemy's turn; enemy actually takes turn at end of timer, and switches to player turn
    int enemyTurnTracker = 0;
    // Keep track of who's turn it currently is
    bool playerTurn = false;
    // Keep track of selected action in hand
    int selectedAction = -1;

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

                        // test
                        case SDLK_RIGHT:
                            enemyPosition.x++;
                        break;
                        case SDLK_LEFT:
                            enemyPosition.x--;
                        break;
                        case SDLK_UP:
                            enemyPosition.y--;
                        break;
                        case SDLK_DOWN:
                            enemyPosition.y++;
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
                            switch (currentScene) {
                                case SCENE::title:
                                    // Detect if play button pressed
                                    if (inBounds(mouseX, mouseY, {(SCREEN_WIDTH * 5) / 16, (SCREEN_HEIGHT * 7) / 9, (SCREEN_WIDTH * 6) / 16, SCREEN_HEIGHT / 9})) {
                                        currentScene = SCENE::game;
                                    }
                                break;
                                
                                case SCENE::game:
                                    if (playerTurn) {
                                        // Use an action
                                        if (selectedAction != -1 && inBounds(mouseX, mouseY, {0, SCREEN_HEIGHT * 11 / 18, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 18})) {
                                            
                                        }

                                        // Discard an action
                                        else if (selectedAction > -1 && inBounds(mouseX, mouseY, {SCREEN_WIDTH / 6, SCREEN_HEIGHT * 11 / 18, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 18})) {
                                            heroActions.discard(selectedAction);
                                            selectedAction = -1;
                                        }
                                        
                                        // Select an action
                                        else if (inBounds(mouseX, mouseY, {SCREEN_WIDTH * 2 / 6, SCREEN_HEIGHT * 11 / 18, SCREEN_WIDTH * 3 / 6, SCREEN_HEIGHT / 18})) {
                                            selectedAction = -(mouseX / (SCREEN_WIDTH / 6));
                                        } else if (inBounds(mouseX, mouseY, {SCREEN_WIDTH / 8, SCREEN_HEIGHT * 12 / 18, SCREEN_WIDTH * 7 / 8, SCREEN_HEIGHT / 3})) {
                                            selectedAction = (mouseX / (SCREEN_WIDTH / 8)) - 1;
                                            // Detect if invalid
                                            if (selectedAction >= heroActions.getNumHand()) {
                                                selectedAction = -1;
                                            }
                                        }

                                        // Deselect action
                                        else {
                                            selectedAction = -1;
                                        }
                                    }
                                break;
                            }
                        break;
                    }
                break;
            }
        }

        if (currentScene == SCENE::game) {
            // If enemy is dead, set new enemy
            if (currentEnemy == "NULL") {
                // for now, just shuffle
                heroActions.shuffle();

                //test with slime by default
                currentEnemy = "slime";
                // Randomize starting position
                while (enemyPosition.x == 0 && enemyPosition.y == 0) {
                    enemyPosition.x = random(-5, 5);
                    enemyPosition.y = random(-5, 5);
                }
                enemyTurnTracker = TPS * 2;
                currentMoves = enemies.at(currentEnemy).nextMoves();
                currentMove = currentMoves.newInstance();
            }

            if (enemyTurnTracker > 0) {
                enemyTurnTracker--;
            } else if (!playerTurn) {
                // Switch to player's turn; take enemy turn, and draw for hand
                playerTurn = true;

                currentThreatened = parseEnemyMove(currentMoves.nextMove(currentMove), enemyPosition);

                try {
                    heroActions.draw();
                } catch (int e) {
                    // do nothing for now
                }
            }
        }

        switch (currentScene) {
            case SCENE::title:
                // Detect if play button selected
                if ((mouseX >= (SCREEN_WIDTH * 5) / 16 && mouseX <= (SCREEN_WIDTH * 11) / 16) && (mouseY >= (SCREEN_HEIGHT * 7) / 9 && mouseY <= (SCREEN_HEIGHT * 8) / 9)) {
                    renderTitleScreen(true);
                } else {
                    renderTitleScreen(false);
                }
            break;

            case SCENE::game:
                renderGameScreen();
                renderActions(heroActions);
                renderSelectedAction(selectedAction);
                renderHero();
                renderEnemy(enemyPosition, enemies.at(currentEnemy).getName());
                renderThreatenedTiles(currentThreatened);
            break;
        }

        // Render final frame
        SDL_RenderPresent(renderer);
        
        // Simulate ticks per second naively
        SDL_Delay(1000/TPS);
    }

	close();

	return 0;
}