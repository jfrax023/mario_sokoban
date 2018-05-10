/**
* Windows.h is a header file for windows.c
* Created by lilith on 10/05/18.
*/

#ifndef MARIO_SOKOBAN_WINDOWS_H
#define MARIO_SOKOBAN_WINDOWS_H

#include <SDL/SDL.h>

/**
 * Set a name and background color
 * @param sRootWindow SDL_Surface the main window
 */
void setNameAndBg(SDL_Surface *sRootWindow);

/**
 * Set an image in the main window according to the parameters passed in argument .
 * @param sRoot SDL_Surface the main window where blit image
 * @param sImg SDL_Surface a surface where the image is
 * @param positionImg SDL_Rect a sdl sturcture with a postion for image
 * @param center Bool 0 if no need to be center 1 else
 */
void setImageInWindow(SDL_Surface *sRoot, SDL_Surface *sImg, SDL_Rect *positionImg, int center);
#endif //MARIO_SOKOBAN_WINDOWS_H
