/**
 * event.h is a header file for events.c
 * Created by lilith on 10/05/18.
 * Function List :
 * -- void pause();
 * -- int getUserChoice(int pFlag);
 * -- void mapMenuEventManager(Map *pMap, int *current, int *menuChoice);
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
 * TMP just a tmp function to back menu 1 from edition
 * @return An flag to put in menuChoice variable .
 */
int waitToBackEdition();
//----------------------------------------------------------------------------------------------------------------------
#endif //MARIO_SOKOBAN_EVENTS_H
