/**
 * game.h is a header for game.c and corresponding to the prototype of function for the game .
 * Created by lilith on 20/05/18.
 * Function list :
 * -- void setElementData(SDL_Surface *sElem, ELEMENT *elem, char id, int block); Set Element structure .
 * -- void setMarioPosition(SDL_Rect *posMario, int x, int y); Set mario position
 * -- int setNextTarget(int current, int move);
 * -- int checkMovement(ELEMENT current, ELEMENT next);
 * -- void setMovement(ELEMENT *S_eElem, SDL_Surface *pRootWindow, SDL_Surface *sElem[],
 *              int *currentElem, int *nextElem, char dirFlag, int move, int *nextBox);
 * -- void cpDataInElement(ELEMENT *S_eTarget, ELEMENT *S_eToCopy);
 * -- void displayObjectifInSurface(ELEMENT *S_elem);
 * -- void removeMarioInElement(ELEMENT *S_Elem);
 * -- void displayObjectifClear(ELEMENT *elem);
 * -- void updateElement(ELEMENT *S_eElem, int *currentElem, int *nextElem, int *nextBox, int *objFlag);
 * --
 */

#ifndef MARIO_SOKOBAN_GAME_H
#define MARIO_SOKOBAN_GAME_H

#include <SDL/SDL.h>
#include "utilities.h"
//----------------------------------------------------------------------------------------------------------------------

/**
 * Initialize value to element structure according to the element is current analysed .
 * @param sElem SDL_Surface The surface corresponding to this element .
 * @param elem Element The structure element .
 * @param id int The letter representing this elements .
 * @param block int Bool Said if this elements is fix or not like wall is fix value = 1 .
 * @param numSurface int A number corresponding to the position in surface array (5 = [5] in array) .
 */
void setElementData(ELEMENT *elem, char id, int block, int numSurface, SDL_Rect *pos, char path[]);

/**
 * Update an element in Element structure to to make it match an objectif no completed element .
 * @param S_elem ELEMENT An pointer to the element to update .
 */
void displayObjectifInSurface(ELEMENT *S_elem);

/**
 * Update an element in Element structure to make it match a objectif clear element .
 * @param elem ELEMENT An pointer to the element to update .
 */
void displayObjectifClear(ELEMENT *elem);

/**
 * Set a potion for mario avatar .
 * @param posMario SDL_Rect An pointer to the var marioPosition .
 * @param x int X position .
 * @param y int Y position .
 */
void setMarioPosition(SDL_Rect *posMario, int x, int y);

/**
 * Clean the target var before new assignation .
 * @param S_eTarget ELEMENT The element to clean .
 */
void cleanElement(ELEMENT *S_eTarget);

/**
 * Copy the data of an element to another .
 * @param S_eTarget ELEMENT An pointer to the element target .
 * @param S_eToCopy ELEMENT An pointer to the element to copy .
 */
void cpDataInElement(ELEMENT *S_eTarget, ELEMENT *S_eToCopy);

/**
 * This function check and call the update function for the structure element .
 * @param S_eElem ELEMENT S_eElem An pointer to the structure element where update the value .
 * @param currentElem int An pointer to the variable currentElement corresponding to the current element (mario)
 * @param nextElem int An pointer to the var nextElem corresponding to the next element .
 * @param nextBox  int An pointer to the var nextBox who tell the next surface after an box if box there .
 * @param objFlag int An pointer to the var objFlag who tell if the next surface is an objective or if an objective need
 *                      to be re display .
 */
void updateElement(ELEMENT *S_eElem, int *currentElem, int *nextElem, int *nextBox, int *objFlag);

/**
 * Update an element where mario avatare has been to a null element .
 * @param S_Elem ELEMENT An pointer to the element to update .
 */
void removeMarioInElement(ELEMENT *S_Elem);

/**
 * Set new position for an element or more .
 * @param S_eElem ELEMENT An pointer to the structure Element where change the value .
 * @param currentElem int The position of the element in structure element .
 * @param dirFlag char A flag (+ -) to tell if we need to addition or substract .
 * @param move int A number corresponding to a bool 0 is a top or bottom move 1 left and right move .
 */
void setPositionForElem(ELEMENT *S_eElem, char dirFlag, int move);

/**
 * Call the next functions to set the differents vlaues before update the main windows .
 * @param S_eElem ELEMENT An pointer to the element sutructure where update and take data .
 * @param pRootWindow SDL_Surface An pointer to the main window .
 * @param sElem SDL_Surface An array of pointer to the elements surface .
 * @param currentElem int An pointer to the current variable corresponding to the position of the current element in an array .
 * @param nextElem int An pointer to the nextElem var corresponding to the position of the next element in an array .
 * @param dirFlag char A symbole + or - to tell if we worked to the width or to the eight .
 * @param move int A number to tell if we move on x or y (0 y other x) .
 * @param nextBox int An pointer to the nextBox var corresponding to the next surface after the box .
 */
void setMovement(ELEMENT *S_eElem, SDL_Surface *pRootWindow, SDL_Surface *sElem[],
                int *currentElem, int *nextElem, char dirFlag, int move, int *nextBox);

/**
 * Check if the movement made by user is in limits of the map .
 * @param current int The current position corresponding to the position in array .
 * @param move int A number corresponding to the next position in array we need to goes .
 * @return int Bool 0 if the movement is impossible 1 else .
 */
int setNextTarget(int current, int move, char dirFlag);


/**
 * Check if the movement is possible .
 * @param nextElem int A number corresponding to the next element .
 * @param elem ELEMENT The element structure to get data .
 * @param move int A number of frame needed to move .
 * @param dirFlag char The direction corresponding to addition or substraction .
 * @return 0 if movement is impossible 1 else .
 */
int checkMovement(int nextElem, ELEMENT elem[], int move, char dirFlag);

//----------------------------------------------------------------------------------------------------------------------
#endif //MARIO_SOKOBAN_GAME_H
