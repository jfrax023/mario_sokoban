/**
 * error_helper.h is a header file for error_helper.c
 * Created by lilith on 10/05/18.
 */

#ifndef MARIO_SOKOBAN_ERROR_HELPER_H
#define MARIO_SOKOBAN_ERROR_HELPER_H

#include <SDL/SDL.h>

/**
 * Check if the sruface is null and raise an error and exit program .
 * @param toCheck The surface will checking .
 * @param message An message to help for debug .
 */
void checkIfSurfaceIsNull(SDL_Surface *toCheck, char message[]);
#endif //MARIO_SOKOBAN_ERROR_HELPER_H
