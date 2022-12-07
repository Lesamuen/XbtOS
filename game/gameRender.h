#ifndef GAMERENDER_H
#define GAMERENDER_H

#include "actions.h"

#include <SDL2/SDL.h>

/* This function handles rendering for the initial title screen.
 * Only two states: whether the play button is hovered or not
 *
 * Input:
 *      playSelected = boolean whether player is hovering over button
 */
void renderTitleScreen(bool playSelected);

/* Renders the static parts of the game screen;
 * 11x11 tile map (from top, 5.5/9 of height)
 * Button bar ((5.5 to 6)/9 height)
 * Deck/cards (width 2/16, bottom 3/9)
 */
void renderGameScreen();

/* Renders the information of the deck and hand of the player.
 */
void renderActions(heroActions& heroActions);

#endif