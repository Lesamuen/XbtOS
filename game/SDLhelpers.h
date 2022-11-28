#ifndef SDLHELPERS_H
#define SDLHELPERS_H

#include <SDL2/SDL.h>

#include <vector>

/* Initialize SDL and create window.
 *
 * Output:
 *      window = SDL_Window pointer containing application window
 * Throws:
 *      0 - Video initialization failure
 *      1 - Window creation failure
 */
SDL_Window* init();

/* Load a given BMP image.
 * A wrapper for SDL_LoadBMP that throws on failure.
 *
 * Input:
 *      path = C-style string with the file path of the image
 * Output:
 *      A pointer to the loaded image in raw pixel data
 * Throws:
 *      0 - Image was unable to be obtained for some reason
 */
SDL_Surface* loadMedia(const char*& path);

/* Load all image files into a vector of SDL_Surfaces in a specified pixel format.
 * TODO: placeholder image (single white pixel?) for all images that fail to load.
 * Uses the list of images defined in defs.h.
 * This is used so that images stay in memory and don't have to be re-loaded every time they are used.
 * 
 * Input:
 *      format = pointer to an SDL_PixelFormat that will be applied to all images
 * Output:
 *      A vector containing pointers to every image loaded
 */
std::vector<SDL_Surface*> loadAllMedia(SDL_PixelFormat*& format);

/* Cleanup SDL environment and close window.
 *
 * Input:
 *      window = main application window to be closed
 *      images = vector of images to be unloaded
 */
void close(SDL_Window*& window, std::vector<SDL_Surface*>& images);

#endif