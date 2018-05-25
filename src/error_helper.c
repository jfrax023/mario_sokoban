/**
 * error_helper.c is a source file withe some function to set a error in code like a control of pointer is null make this etc
 * Created by lilith on 10/05/18.
 */
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "utilities.h"

//----------------------------------------------------------------------------------------------------------------------
/**
 * Check if the sruface is null and raise an error and exit program
 * @param toCheck The surface will checking
 * @param message An message to help for debug
 */
void checkIfSurfaceIsNull(SDL_Surface *toCheck, char message[]){
    if(toCheck == NULL){
        fprintf(stderr, "%s => %s\n", message, SDL_GetError());
        exit(EXIT_FAILURE);
    }
}


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
int checkIfMapIsCorrect(ELEMENT *S_Elem, int nbObjectif){
    int mario = 0;
    int box = 0;
    int obj = 0;
    for(int i = 0; i < MAP_MAX_SIZE; i++){
        switch(S_Elem[i].id){
            case E_BOX:
                box++;
                break;
            case E_GOAL:
                obj++;
                break;
            case E_MARIO_TOP:
                mario++;
                break;
            case E_MARIO_RIGHT:
                mario++;
                break;
            case E_MARIO_BOT:
                mario++;
                break;
            case E_MARIO_LEFT:
                mario++;
                break;
            default:
                ;
        }
    }
    if(box != nbObjectif){
        return 0;
    }
    if(obj != nbObjectif){
        return 0;
    }
    if(mario != 1){
        return 0;
    }
    return 1;
}


/**
 * Check if the last frame in a line is a wall to define the border of the map .
 * @param S_Elem ELEMENT An pointer to the array of element structure .
 * @return int bool 1 if map is correct 0 else ;
 */
int checkIfBorderIsCorrect(ELEMENT *S_Elem){
    for(int i = 0; i < MAP_MAX_SIZE; i++){
        if((i + 1) % NB_FRAME_IN_LINE == 0){
            // nb Frame is 16 we need to subtract one to corresponding at the last elements in a line .
            if(S_Elem[i].id == E_WALL || S_Elem[i].id == E_GOAL || S_Elem[i].id == E_MARIO_BOT || S_Elem[i].id == E_MARIO_LEFT
                    || S_Elem[i].id == E_MARIO_RIGHT || S_Elem[i].id == E_MARIO_TOP){
                return 1;
            }
        }
    }
    return 0;
}

/**
 * Check if the last frame in a line is a wall to define the border of the map .
 * @param S_Elem ELEMENT An pointer to the array of element structure .
 * @return int bool 1 if map is correct 0 else ;
 */
int checkNumberOfFreeCase(ELEMENT *S_Elem){
    int caseFree = 0;
    for(int i = 0; i < MAP_MAX_SIZE; i++){
        if(S_Elem[i].id == E_NULL){
           caseFree++;
        }
    }
    if(caseFree < NB_CASE_FREE_MIN){
        return 0;
    }
    return 1;
}





//----------------------------------------------------------------------------------------------------------------------

