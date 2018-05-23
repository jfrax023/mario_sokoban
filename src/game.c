/**
 * game.c is a source file where we define the function for the game .
 * Created by lilith on 20/05/18.
 */

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include "utilities.h"
#include "events.h"
#include "windows.h"
#include <string.h>
#include "game.h"
//----------------------------------------------------------------------------------------------------------------------

/**
 * Clean the target var before new assignation .
 * @param S_eTarget ELEMENT The element to clean .
 */
void cleanElement(ELEMENT *S_eTarget){
    S_eTarget->id = 0;
    S_eTarget->x = 0;
    S_eTarget->y = 0;
    for(int i = 0;i < A_HALF_HUNDR;i++){
        S_eTarget->pathImg[i] = 0;
    }
}

/**
 * Initialize value to element structure according to the element is current analysed .
 * @param sElem SDL_Surface The surface corresponding to this element .
 * @param elem Element The structure element .
 * @param id int The letter representing this elements .
 * @param block int Bool Said if this elements is fix or not like wall is fix value = 1 .
 * @param numSurface int A number corresponding to the position in surface array (5 = [5] in array) .
 */
void setElementData(ELEMENT *elem, char id, int block, int numSurface, SDL_Rect *pos, char path[]) {
    elem->id = id;
    elem->block = block;
    elem->numSurface = numSurface;
    elem->x = pos->x;
    elem->y = pos->y;
    elem->limitX = pos->x + E_WIDTH;
    elem->limitY = pos->y + E_HEIGHT;
    strcpy(elem->pathImg, path);
}

/**
 * Copy mario top data in an elment
 * @param S_eTarget ELEMENT The target where we copy data .
 * @param S_eMario ELEMENT The current element here mario .
 */
void copyMarioTop(ELEMENT *S_eTarget, ELEMENT *S_eMario){
    cleanElement(S_eTarget);
    S_eTarget->id = E_MARIO_TOP;
    S_eTarget->y = S_eMario->y;
    S_eTarget->x = S_eMario->x;
    strcpy(S_eTarget->pathImg, MARIO_TOP_PATH);
}

/**
 * Copy mario bottom data in an elment
 * @param S_eTarget ELEMENT The target where we copy data .
 * @param S_eMario ELEMENT The current element here mario .
 */
void copyMarioBot(ELEMENT *S_eTarget, ELEMENT *S_eMario){
    cleanElement(S_eTarget);
    S_eTarget->id = E_MARIO_BOT;
    S_eTarget->y = S_eMario->y;
    S_eTarget->x = S_eMario->x;
    strcpy(S_eTarget->pathImg, MARIO_BOT_PATH);
}


/**
 * Copy mario right data in an elment
 * @param S_eTarget ELEMENT The target where we copy data .
 * @param S_eMario ELEMENT The current element here mario .
 */
void copyMarioRight(ELEMENT *S_eTarget, ELEMENT *S_eMario){
    cleanElement(S_eTarget);
    S_eTarget->id = E_MARIO_RIGHT;
    S_eTarget->y = S_eMario->y;
    S_eTarget->x = S_eMario->x;
    strcpy(S_eTarget->pathImg, MARIO_RIGHT_PATH);
}


/**
 * Copy mario left data in an elment
 * @param S_eTarget ELEMENT The target where we copy data .
 * @param S_eMario ELEMENT The current element here mario .
 */
void copyMarioLeft(ELEMENT *S_eTarget, ELEMENT *S_eMario){
    cleanElement(S_eTarget);
    S_eTarget->id = E_MARIO_LEFT;
    S_eTarget->y = S_eMario->y;
    S_eTarget->x = S_eMario->x;
    strcpy(S_eTarget->pathImg, MARIO_LEFT_PATH);
}



/**
 * Update an element in Element structure to make it match a objectif clear element .
 * @param elem ELEMENT An pointer to the element to update .
 */
void displayObjectifClear(ELEMENT *elem){
    cleanElement(elem);
    elem->id = E_BOX_OK;
    elem->block = 1;
    elem->x = elem->limitX - E_WIDTH;
    elem->y = elem->limitY - E_HEIGHT;
    strcpy(elem->pathImg, BOX_OK_PATH);
}


/**
 * Update an element in Element structure to to make it match an objectif no completed element .
 * @param S_elem ELEMENT An pointer to the element to update .
 */
void displayObjectifInSurface(ELEMENT *S_elem){
    cleanElement(S_elem);
    S_elem->id = E_GOAL;
    S_elem->x = S_elem->limitX - E_WIDTH;
    S_elem->y = S_elem->limitY - E_HEIGHT;
    strcpy(S_elem->pathImg, GOAL_PATH);
}


/**
 * Update an element where mario avatare has been to a null element .
 * @param S_Elem ELEMENT An pointer to the element to update .
 */
void removeMarioInElement(ELEMENT *S_Elem){
    cleanElement(S_Elem);
    S_Elem->id = E_NULL;
    S_Elem->y = S_Elem->limitY - E_HEIGHT;
    S_Elem->x = S_Elem->limitX - E_WIDTH;
    strcpy(S_Elem->pathImg, "null");
}

/**
 * Set a potion for mario avatar .
 * @param posMario SDL_Rect An pointer to the var marioPosition .
 * @param x int X position .
 * @param y int Y position .
 */
void setMarioPosition(SDL_Rect *posMario, int x, int y){
    posMario->y = (u_int16_t) y;
    posMario->x = (u_int16_t) x;
}
/**
 * Copy the data of an element to another .
 * @param S_eTarget ELEMENT An pointer to the element target .
 * @param S_eToCopy ELEMENT An pointer to the element to copy .
 */
void cpDataInElement(ELEMENT *S_eTarget, ELEMENT *S_eToCopy){
    cleanElement(S_eTarget);
    S_eTarget->id = S_eToCopy->id;
    S_eTarget->x = S_eToCopy->x;
    S_eTarget->y = S_eToCopy->y;
    strcpy(S_eTarget->pathImg, S_eToCopy->pathImg);
}


/**
 * Call the correct function according to the move and dirFlag parameters .
 * @param S_eTarget ELEMENT An pointer to the element target .
 * @param S_eToCopy ELEMENT An pointer to the element to copy .
 * @param move int A number corresponding to the direction where we going 1 left and right other top and bot
 * @param dirFlag A symbole + or - to tell if we go top or bot or right or left .
 */
void callMarioCopy(ELEMENT *S_eTarget, ELEMENT *S_eMario, int move, char dirFlag){
    if(move == 1){
        if(dirFlag == '+'){
            // move right
            // copy mario in next
            copyMarioRight(S_eTarget, S_eMario);
        } else{
            copyMarioLeft(S_eTarget, S_eMario);
        }
    } else{
        if(dirFlag == '+'){
            // move right
            // copy mario in next
            copyMarioBot(S_eTarget, S_eMario);
        } else{
            copyMarioTop(S_eTarget, S_eMario);
        }
    }
}


/**
 * This function check and call the update function for the structure element .
 * @param S_eElem ELEMENT An pointer to the structure element where update the value .
 * @param currentElem int An pointer to the variable currentElement corresponding to the current element (mario)
 * @param nextElem int An pointer to the var nextElem corresponding to the next element .
 * @param nextBox  int An pointer to the var nextBox who tell the next surface after an box if box there .
 * @param objFlag int An pointer to the var objFlag who tell if the next surface is an objective or if an objective need
 *                      to be re display .
 */
void updateElement(ELEMENT *S_eElem, int *currentElem, int *nextElem, int *nextBox, int *objFlag,
                   int move, char dirFlag, int *nbObjectif){

    if(!*objFlag){
        //no objective no box
        if(*nextBox == 0){
            // mario image condition
            callMarioCopy(&S_eElem[*nextElem], &S_eElem[*currentElem], move, dirFlag);
            // remove mario
            removeMarioInElement(&S_eElem[*currentElem]);
            // and set nextElem and current to new surface
            *currentElem = *nextElem;
            *nextElem = 0;

        } else{
            // copy next elem (a box here) in next surface after here
            cpDataInElement(&S_eElem[*nextBox], &S_eElem[*nextElem]);
            // copy current elem (here mario) to next elem (next surface)
            callMarioCopy(&S_eElem[*nextElem], &S_eElem[*currentElem], move, dirFlag);
            // and finally remove data to current mario position by a null element .
            removeMarioInElement(&S_eElem[*currentElem]);
            // and set nextElem, nextBox to 0, and current to new surface
            *currentElem = *nextElem;
            *nextBox = 0;
            *nextElem = 0;

        }
    } else{
        // here the next surface where we going as an objective .
        if(*nextBox == 0){
            // no box we need to know if objFlag corresponding to the next surface or if we need to set them at mario position
            if(*objFlag != *currentElem){
                // we need to remove objective image by mario image and set the current position in objFlag
                callMarioCopy(&S_eElem[*nextElem], &S_eElem[*currentElem], move, dirFlag);
                // remove mario
                removeMarioInElement(&S_eElem[*currentElem]);
                *currentElem = *nextElem;
                *objFlag = *currentElem; // we save the position of the objective
                *nextElem = 0;
            } else{
                // copy mario to next
                callMarioCopy(&S_eElem[*nextElem], &S_eElem[*currentElem], move, dirFlag);
                // re set obj data
                displayObjectifInSurface(&S_eElem[*currentElem]);
                // update data
                *currentElem = *nextElem;
                *nextElem = 0;
                *objFlag = 0;
            }
        } else{
            // if objFlag corresponding to the next surface or we need to set them at mario position
            if(*objFlag != *currentElem){
                // a box and objective is the next surface we need to display the objective clear image .
                displayObjectifClear(&S_eElem[*nextBox]);
                // current elem go to next elem
                callMarioCopy(&S_eElem[*nextElem], &S_eElem[*currentElem], move, dirFlag);
                // remove mario
                removeMarioInElement(&S_eElem[*currentElem]);
                *currentElem = *nextElem;
                *objFlag = 0; // we save the position of the objective
                *nextElem = 0;
                // and an objective is completed
                *nbObjectif = *nbObjectif - 1;
            } else{
                // copy mario to next
                callMarioCopy(&S_eElem[*nextElem], &S_eElem[*currentElem], move, dirFlag);
                // re set obj data
                displayObjectifInSurface(&S_eElem[*currentElem]);
                // update data
                *currentElem = *nextElem;
                *nextElem = 0;
                *objFlag = 0;

            }
        }

    }
}


/**
 * Set new position for an element passed in parameter .
 * @param S_eElem ELEMENT An pointer to the structure Element where change the value .
 * @param currentElem int The position of the element in structure element .
 * @param dirFlag char A flag (+ -) to tell if we need to addition or substract .
 * @param move int A number corresponding to a bool 0 is a top or bottom move 1 left and right move .
 */
void setPositionForElem(ELEMENT *S_eElem, char dirFlag, int move){
    if(dirFlag == '+'){
        // 0 corresponding to the y (eight) .
        if(move == 1){
            S_eElem->x += E_WIDTH;
        } else{
            S_eElem->y += E_HEIGHT;
        }
    } else if(dirFlag == '-'){
        if(move == 1){
            S_eElem->x -= E_WIDTH;
        } else{
            S_eElem->y -= E_HEIGHT;
        }
    }
}


/**
 * Check if the movement made by user is in limits of the map .
 * @param current int The current position corresponding to the position in array .
 * @param move int A number corresponding to the next position in array we need to goes .
 * @param dirFlag char A character + or - to tell if we move to bottom or top .
 * @return int Bool 0 if the movement is impossible the position of next element else .
 */
int setNextTarget(int current, int move, char dirFlag){

    if(dirFlag == '-'){
        if( (current - move) < 0){
            return 0;
        } else{
            return current - move;
        }
    } else if(dirFlag == '+'){
        if( (current + move) > MAP_MAX_SIZE){
            return 0;
        } else{
            return current + move;
        }
    } else{
        fprintf(stderr, "Warning flag erreur unknow => %c", dirFlag);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}

/**
 * This function set the number of objective the map has .
 * @param MapToPlay Map The map chosen by the user .
 * @return The number of objective map has .
 */
int getNbObjectif(Map *MapToPlay){
    int static objectif = 0;
    if(MapToPlay != NULL){
        for(int i = 0; i < A_HALF_THOUS;i++){
            if(MapToPlay->content[i] == E_GOAL){
                objectif++;
            }
        }
    }
    return objectif;
}



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
                int *currentElem, int *nextElem, char dirFlag, int move, int *nextBox, int *nbObjectif){
    // this flag need to be change but not re affected .
    int static objFlag = 0;

    switch(S_eElem[*nextElem].id){
        case E_NULL:
        	// set a new position for current element (mario) .
            setPositionForElem(&S_eElem[*currentElem], dirFlag, move);

            // update position for next step
            updateElement(S_eElem, currentElem, nextElem, nextBox, &objFlag, move, dirFlag, nbObjectif);
            updateMainWindow(pRootWindow, sElem, S_eElem, *currentElem, *nextElem);
            break;
        case E_BOX:
            // have a box we need to update two position the box and mario
            setPositionForElem(&S_eElem[*currentElem], dirFlag, move);
            setPositionForElem(&S_eElem[*nextElem], dirFlag, move);
            // update
            if(S_eElem[*nextBox].id == E_GOAL && objFlag == 0){
                // we need to set objFlag to indicate is in the next surface
                objFlag = 1;
            }
            // update position for next step
            updateElement(S_eElem, currentElem, nextElem, nextBox, &objFlag, move, dirFlag, nbObjectif);
            // update window
            updateMainWindow(pRootWindow, sElem, S_eElem, *currentElem, *nextElem);
            break;
        case E_GOAL:
            setPositionForElem(&S_eElem[*currentElem], dirFlag, move);

            if(S_eElem[*nextElem].id == E_GOAL && objFlag == 0){
                // we need to set objFlag to indicate is in the next surface
                objFlag = 1;
            }
            // update position for next step
            updateElement(S_eElem, currentElem, nextElem, nextBox, &objFlag, move, dirFlag, nbObjectif);
            // update window
            updateMainWindow(pRootWindow, sElem, S_eElem, *currentElem, *nextElem);
            break;
        default:
            ;
    }
}


/**
 * Check if the movement is possible .
 * @param nextElem int A number corresponding to the next element .
 * @param elem ELEMENT The element structure to get data .
 * @param move int A number of frame needed to move .
 * @param dirFlag char The direction corresponding to addition or substraction .
 * @return 0 if movement is impossible 1 else .
 */
int checkMovement(int nextElem, ELEMENT elem[], int move, char dirFlag){
    // to avoid box we need to know what is the element after a box to define if the movement is
    // possible or not .
    int tmp = 0;
    if(elem[nextElem].id == E_BOX)
        tmp = setNextTarget(nextElem, move, dirFlag);
    // move impossible .
    if(nextElem == 0)
        return 0;
    if(elem[nextElem].block == 1)
        return 0;
    // out of limit
    if(elem[nextElem].id == E_BOX && tmp == 0)
        return 0;
    if(elem[nextElem].id == E_BOX && elem[tmp].id == E_WALL)
        return 0;
    if(elem[nextElem].id == E_BOX && elem[tmp].id == E_BOX)
    	return 0;
    if(elem[nextElem].id == E_BOX_OK)
        return 0;
    
    
    if(elem[nextElem].id == E_BOX){

    	return tmp;
    } else{
    	return 1;
    }
}

//----------------------------------------------------------------------------------------------------------------------

