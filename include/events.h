/**
 * event.h is a header file for events.c
 * Created by lilith on 10/05/18.
 * Function List :
 * -- void pause();
 * -- int getUserChoice(int pFlag);
 * -- void mapMenuEventManager(Map *pMap, int *current, int *menuChoice);
 * -- gameStartEvent();
 * -- void gameEventManager(SDL_Surface *pRootWindow, SDL_Surface *sElem[], ELEMENT *elem, int numSurfaceMario);
 * -- int editionEventManager(ELEMENT elem[], int *cursor, int *tmpChoice, int *nbObj);
 */

#ifndef MARIO_SOKOBAN_EVENTS_H
#define MARIO_SOKOBAN_EVENTS_H

#include "utilities.h"
//----------------------------------------------------------------------------------------------------------------------
/**
 * Simple function to put the programme in pause mode until a SDL_QUIT event detected .
 */
void pause();

/**
 * This function allow to manage a keyboard event and recovery what the user have choose according to menu image .
 * The choices possible is defined by the parameter passed in argument and defined by the number of choice it is
 * possible to make in this menu like first menu have 2 possibilities and the second have 3 possibilities .
 * @param int pFlag An integer corresponding to the number of choice possible .
 * @return int The number choosed by user .
 */
int getUserChoice(int pFlag);


/**
 * This function manage the choice made by the user and set the next step in current .
 * @param pMap An pointer to the map structure to access at next and previous var .
 * @param current int An pointer to the current variable used to move to the next step .
 */
void mapMenuEventManager(Map *pMap, int *current, int *menuChoice);

/**
 * Juste wait a return event to start game in main
 */
void gameStartEvent();

/**
 * Event manager for game event .
 * @param pRootWindow SDL_Surface An pointer to the main window .
 * @param sElem SDL_Surface An pointer to an array of surface corresponding to elements surface .
 * @param elem ELEMENT An pointer to the array of Element structure .
 * @param numSurfaceMario int The position of mario in map .
 */
void gameEventManager(SDL_Surface *pRootWindow, SDL_Surface *sElem[], ELEMENT *elem, int numSurfaceMario);

/**
 * Event manager for edition mode .
 * @param pRootWindow SDL_Surface An pointer to the main window .
 * @param sElem SDL_Surface An pointer to an array of surface corresponding to elements surface .
 * @param elem ELEMENT An pointer to the array of Element structure .
 * @param cursor int An pointer to the variable cursor representing the current position or element where we work .
 * @param tmpChoice int An pointer on the variable tmpChoice to tell continue or get out while .
 * @param nbObj int An pointer on the variable nbObjectif .
 */
int editionEventManager(ELEMENT elem[], int *cursor, int *tmpChoice, int *nbObj);


//----------------------------------------------------------------------------------------------------------------------
#endif //MARIO_SOKOBAN_EVENTS_H
