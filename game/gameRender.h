#ifndef GAMERENDER_H
#define GAMERENDER_H

#include <SDL2/SDL.h>

/* This function handles rendering for the initial title screen.
 * Only two states: whether the play button is hovered or not
 *
 * Input:
 *      playSelected = boolean whether player is hovering over button
 */
void renderTitleScreen(bool playSelected);

#endif