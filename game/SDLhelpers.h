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
 *      2 - Window creation failure
 *      3 - Renderer creation failure
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

/* Cleanup SDL environment and close window.
 *
 * Input:
 *      window = main application window to be closed
 *      images = vector of images to be unloaded
 * 
 * Throws:
 *      0 - List of image paths not found
 */
void close (SDL_Window*& window, std::unordered_map<std::string, SDL_Texture*>& images);

#endif