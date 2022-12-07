#ifndef SDLHELPERS_H
#define SDLHELPERS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <unordered_map>
#include <string>

/* Initialize SDL and create window.
 *
 * Output:
 *      window = SDL_Window pointer containing application window
 * Throws:
 *      0 - Video initialization failure
 *      1 - PNG Loading system initialization failure
 *      2 - Font loading system initialization failure
 *      3 - Window creation failure
 *      4 - Renderer creation failure
 *      5 - Failed to load the font for the game
 */
void init();

/* Load a given PNG (lossless and compressed) image, and put it onto the global images map
 * A wrapper for IMG_Load that throws on failure.
 *
 * Input:
 *      path = string with the file path of the image
 *      format = format to encode the loaded image in
 * Throws:
 *      0 - Image was unable to be obtained for some reason
 *      1 - Obtained image was unable to be converted
 */
void loadMedia(const std::string& path);

/* Call loadMedia for all images currently being used in the game.
 * Uses img/imagePaths.txt for list of images to be loaded.
 * All images are assumed to be in img/
 * 
 * Throws:
 *      0 - Image unable to be loaded
 */
void loadStandardMedia();

/* Returns the texture for the text.
 * Tries to get it from the previously created ones in memory.
 * If not available, creates a new texture, to prevent too much resource cost.
 * 
 * Input:
 *      text = the string that is the contents of the wanted texture
 *      color = the SDL_Color of the text
 * 
 * Throws:
 *      0 - Unable to render text surface
 *      1 - Unable to convert surface to texture
 */
SDL_Texture* renderText(const std::string& text, const SDL_Color& color);

/* Cleanup SDL environment and close window.
 */
void close();

/* Fits a given box to a bounding SDL_Rect variably
 */
SDL_Rect fitRect(const int& width, const int& height, const SDL_Rect& bound);

/* Tests if a point is within bounds of a given rectangle.
 */
bool inBounds(const int& testX, const int& testY, const SDL_Rect& bound);

#endif