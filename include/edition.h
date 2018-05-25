/**
 * edition.h is a header for edition.c where we define functions to display and allow the edition mode .This mode allows
 *  created map by using a keyboard event and build step by step a new map for game .
 *  Created by lilith on 24/05/18.
 *
 *  Function Lists :
 *  -- void setNbObjectifByMode(int lvlMode, int *nbObjectif);
 *  -- void diplayEditionMode(SDL_Surface *pRootWindow, int *menuChoice);
 *  -- void initElementArray(ELEMENT *PS_Elem, int x, int y);
 *  -- void checkAndUpdatePathElement(ELEMENT *S_elem, int current, int next);
 */

#ifndef MARIO_SOKOBAN_EDITION_H
#define MARIO_SOKOBAN_EDITION_H

#include <SDL_video.h>

//----------------------------------------------------------------------------------------------------------------------

/**
 * Set the number of objective is possible to create based on the difficulty selected .
 * @param lvlMode int A number to tell the difficulty chosen (1 = easy ...)
 * @param nbObjectif int An pointer to the variable nbObjectif where put the value .
 */
void setNbObjectifByMode(int lvlMode, int *nbObjectif);

/**
 * This function display and manage the edition mode for creating a new map for the game .
 * @param pRootWindow SDL_Surface An pointer to the main window .
 * @param menuChoice int An pointer to the variable menuChoice who allow to navigate between menu .
 */
void diplayEditionMode(SDL_Surface *pRootWindow, int *menuChoice);

/**
 * Initialize the Element array to null value .
 * @param psElem ELEMENT An pointer to the array of Element .
 */
void initElementArray(ELEMENT *PS_Elem, int x, int y);

/**
 * Check if the pathImage variable for an element is null and set them to green, aslo remove green in previous elements
 *  if is .
 * @param S_elem ELEMENT An pointer to the array of element structure .
 * @param current int A position of current element .
 * @parm next int A position of the next element .
 */
void checkAndUpdatePathElement(ELEMENT *S_elem, int current, int next);




//----------------------------------------------------------------------------------------------------------------------
#endif //MARIO_SOKOBAN_EDITION_H
