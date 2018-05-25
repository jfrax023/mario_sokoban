/**
 * error_helper.h is a header file for error_helper.c
 * Created by lilith on 10/05/18.
 * Function lists :
 *
 * -- void checkIfSurfaceIsNull(SDL_Surface *toCheck, char message[]);
 * -- int checkIfMapIsCorrect(ELEMENT *S_Element, int nbObjectif);
 * -- int checkIfBorderIsCorrect(ELEMENT *S_Elem);
 * -- int checkNumberOfFreeCase(ELEMENT *S_Elem);
 * --
 * --
 */

#ifndef MARIO_SOKOBAN_ERROR_HELPER_H
#define MARIO_SOKOBAN_ERROR_HELPER_H

#include <SDL/SDL.h>
//----------------------------------------------------------------------------------------------------------------------
/**
 * Check if the sruface is null and raise an error and exit program .
 * @param toCheck The surface will checking .
 * @param message An message to help for debug .
 */
void checkIfSurfaceIsNull(SDL_Surface *toCheck, char message[]);


/**
 * Check if the map created by user is correct and have this element in :
 *  - Mario (top, bot, left or right) = 1
 *  - Box 3, 4, 5 according to the difficulties .
 *  - Objectives 3, 4, 5 according to the difficulties .
 *
 * @param S_Elem ELEMENT An pointer to the array of element structure .
 * @param int A number of objectives the map have according to the difficulty .
 * @return int bool 1 if map is correct 0 else ;
 */
int checkIfMapIsCorrect(ELEMENT *S_Elem, int nbObjectif);


/**
 * Check if the last frame in a line is a wall to define the border of the map .
 * @param S_Elem ELEMENT An pointer to the array of element structure .
 * @return int bool 1 if map is correct 0 else ;
 */
int checkIfBorderIsCorrect(ELEMENT *S_Elem);


/**
 * Check if the last frame in a line is a wall to define the border of the map .
 * @param S_Elem ELEMENT An pointer to the array of element structure .
 * @return int bool 1 if map is correct 0 else ;
 */
int checkNumberOfFreeCase(ELEMENT *S_Elem);
//----------------------------------------------------------------------------------------------------------------------
#endif //MARIO_SOKOBAN_ERROR_HELPER_H
