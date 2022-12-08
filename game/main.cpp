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
    std::string currentEnemy = "null";
    coordinate enemyPosition = {0, 0};
    moveGroup currentMoves;
    int* currentMove = new int;
    // Keep track of current threatened tiles on the grid
    std::vector<threatenedTile> currentThreatened;
    // Keep track of player's current charge level
    int charge = 0;

    // Keep track of remaining "time" in ticks in enemy's turn; enemy actually takes turn at end of timer, and switches to player turn
    int enemyTurnTracker = 0;
    // Keep track of battle transition time; 5 seconds
    int enemyRespawnTimer = 0;

    // Keep track of who's turn it currently is
    bool playerTurn = false;
    // Keep track of selected action in hand
    int selectedAction = -1;
    // Keep track of whether a player movement square needs to be selected
    bool selectingMovement = false;
    // Keep track of selected movement tile
    coordinate selectedMovement = {0, 0};
    // Copy of the action the player is trying to use
    action currentAction = actions.at("null");

    // Keep track of deaths for scene transitions
    bool playerDead = false;
    bool enemyDead = true;

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
                                        if (!selectingMovement && selectedAction != -1 && inBounds(mouseX, mouseY, {0, SCREEN_HEIGHT * 11 / 18, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 18})) {
                                            // Remove card and end turn
                                            if (selectedAction >= 0){
                                                heroActions.discard(selectedAction);
                                            }
                                            selectedAction = -1;
                                            playerTurn = false;

                                            // Resolve movement
                                            enemyPosition.x -= selectedMovement.x;
                                            enemyPosition.y -= selectedMovement.y;
                                            for (int i = 0; i < (int) currentThreatened.size(); i++) {
                                                currentThreatened.at(i).x -=selectedMovement.x;
                                                currentThreatened.at(i).y -=selectedMovement.y;
                                            }
                                            selectedMovement = {0, 0};

                                            // Resolve charge
                                            if (charge < enemies.at(currentEnemy).getPower()) {
                                                charge += currentAction.charge;
                                                if (charge > enemies.at(currentEnemy).getPower()) {
                                                    charge = enemies.at(currentEnemy).getPower();
                                                }
                                            }

                                            // Striking takes priority over death
                                            // For now, can only strike while adjacent or diagonal to enemy
                                            if (currentAction.strike && (charge == enemies.at(currentEnemy).getPower()) && (enemyPosition.x >= -1 && enemyPosition.x <= 1 && enemyPosition.y >= -1 && enemyPosition.y <= 1)) {
                                                enemyDead = true;
                                                currentAction = actions.at("null");
                                                break;
                                            }
                                            
                                            // Detect if dead
                                            // Test if any threatened tiles are in 0,0, then test if current action blocks that damage type
                                            for (int i = 0; i < (int) currentThreatened.size(); i++) {
                                                if (currentThreatened.at(i).x == 0 && currentThreatened.at(i).y == 0) {
                                                    playerDead = true;
                                                    for (int j = 0; j < (int) currentAction.blocks.size(); j++) {
                                                        if (currentAction.blocks.at(j) == currentThreatened.at(i).type) {
                                                            playerDead = false;
                                                            break;
                                                        }
                                                    }
                                                    if (playerDead) {
                                                        // If dead, switch to game over screen
                                                        currentScene = SCENE::gameover;
                                                    }
                                                    break;
                                                }
                                            }

                                            currentAction = actions.at("null");
                                            if (!playerDead) {
                                                enemyTurnTracker = 2 * TPS;
                                            }
                                        }

                                        // Discard an action
                                        else if (selectedAction > -1 && inBounds(mouseX, mouseY, {SCREEN_WIDTH / 6, SCREEN_HEIGHT * 11 / 18, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 18})) {
                                            heroActions.discard(selectedAction);
                                            selectedAction = -1;
                                            selectingMovement = false;
                                            selectedMovement = {0, 0};
                                            currentAction = actions.at("null");
                                        }
                                        
                                        // Select an action
                                        else if (inBounds(mouseX, mouseY, {SCREEN_WIDTH * 2 / 6, SCREEN_HEIGHT * 11 / 18, SCREEN_WIDTH * 4 / 6, SCREEN_HEIGHT / 18})) {
                                            selectedAction = -(mouseX / (SCREEN_WIDTH / 6));
                                            if (selectedAction == -2) {
                                                currentAction = actions.at("pass");
                                            } else if (selectedAction == -3) {
                                                currentAction = actions.at("sidestep");
                                            } else if (selectedAction == -4) {
                                                currentAction = actions.at("charge");
                                            } else if (selectedAction == -5) {
                                                currentAction = actions.at("strike");
                                            }
                                        } else if (inBounds(mouseX, mouseY, {SCREEN_WIDTH / 8, SCREEN_HEIGHT * 12 / 18, SCREEN_WIDTH * 7 / 8, SCREEN_HEIGHT / 3})) {
                                            selectedAction = (mouseX / (SCREEN_WIDTH / 8)) - 1;
                                            // Detect if invalid
                                            if (selectedAction >= heroActions.getNumHand()) {
                                                selectedAction = -1;
                                                selectingMovement = false;
                                                selectedMovement = {0, 0};
                                                currentAction = actions.at("null");
                                            } else {
                                                currentAction = heroActions.getHandAction(selectedAction);
                                                if ((int) currentAction.moves.size() > 0) {
                                                    selectingMovement = true;
                                                }
                                            }
                                        }

                                        // Select a movement tile
                                        else if (selectingMovement && inBounds(mouseX, mouseY, {SCREEN_WIDTH * 21 / 64, 0, SCREEN_WIDTH * 11 / 32, SCREEN_HEIGHT * 11 / 18})) {
                                            // Transform mouse coordinates to grid coordinates
                                            int gridX = (mouseX - SCREEN_WIDTH * 21 / 64) / (SCREEN_WIDTH / 32) - 5;
                                            int gridY = (mouseY) / (SCREEN_HEIGHT / 18) - 5;

                                            // Test if there is a movement tile at this location; enemy position invalid
                                            for (int i = 0; i < (int) currentAction.moves.size(); i++) {
                                                if ((currentAction.moves.at(i).x != enemyPosition.x || currentAction.moves.at(i).y != enemyPosition.y) && (gridX == currentAction.moves.at(i).x && gridY == currentAction.moves.at(i).y)) {
                                                    selectingMovement = false;
                                                    selectedMovement = currentAction.moves.at(i);
                                                    break;
                                                }
                                            }
                                        }

                                        // Deselect action
                                        else {
                                            selectedAction = -1;
                                            selectingMovement = false;
                                            selectedMovement = {0, 0};
                                            currentAction = actions.at("null");
                                        }
                                    }
                                break;

                                case SCENE::gameover:
                                    // TODO: implement restart
                                break;
                            }
                        break;
                    }
                break;
            }
        }

        if (currentScene == SCENE::game) {
            // If enemy is dead, set new enemy after a timer
            if (enemyRespawnTimer > 0) {
                enemyRespawnTimer--;
            } else if (enemyDead) {
                // Reset hero
                heroActions.shuffle();
                charge = 0;

                enemyDead = false;
                // TEST with just slime for now
                currentEnemy = "slime";
                // Randomize starting position
                while (enemyPosition.x == 0 && enemyPosition.y == 0) {
                    enemyPosition.x = random(-5, 5);
                    enemyPosition.y = random(-5, 5);
                }
                enemyTurnTracker = TPS * 2;
                currentMoves.removeInstance(currentMove);
                currentMoves = enemies.at(currentEnemy).nextMoves();
                currentMove = currentMoves.newInstance();
            }

            if (enemyTurnTracker > 0) {
                enemyTurnTracker--;
            } else if (!playerTurn) {
                // Switch to player's turn; take enemy turn, and draw for hand
                playerTurn = true;

                try {
                    currentThreatened = parseEnemyMove(currentMoves.nextMove(currentMove), enemyPosition);
                } catch (int e) {
                    if (e == 0) {
                        currentMoves.removeInstance(currentMove);
                        currentMoves = enemies.at(currentEnemy).nextMoves();
                        currentMove = currentMoves.newInstance();
                        currentThreatened = parseEnemyMove(currentMoves.nextMove(currentMove), enemyPosition);
                    }
                }

                selectedMovement = {0, 0};
                try {
                    heroActions.draw();
                } catch (int e) {
                    // do nothing for now
                }
            }
        }

        // Rendering decisions
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
                renderHero((double) charge / enemies.at(currentEnemy).getPower());
                renderEnemy(enemyPosition, enemies.at(currentEnemy).getName());
                renderThreatenedTiles(currentThreatened);
                renderMovementTiles(currentAction.moves, selectedMovement, enemyPosition);
            break;

            case SCENE::gameover:
                // Detect if play button selected
                if ((mouseX >= (SCREEN_WIDTH * 5) / 16 && mouseX <= (SCREEN_WIDTH * 11) / 16) && (mouseY >= (SCREEN_HEIGHT * 7) / 9 && mouseY <= (SCREEN_HEIGHT * 8) / 9)) {
                    renderGameOverScreen(true);
                } else {
                    renderGameOverScreen(false);
                }
            break;
        }

        // Render final frame
        SDL_RenderPresent(renderer);
        
        // Simulate ticks per second naively
        SDL_Delay(1000/TPS);
    }

    delete currentMove;
	close();

	return 0;
}