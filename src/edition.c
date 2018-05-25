/**
 * edition.c is a source file where we define functions to display and allow the edition mode .This mode allows
 *  created map by using a keyboard event and build step by step a new map for game .
 *  Created by lilith on 24/05/18.
 */

#include <stdlib.h>
#include <stdio.h>
#include "utilities.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include "file_helper.h"
#include "windows.h"
#include "edition.h"
#include "events.h"

//----------------------------------------------------------------------------------------------------------------------

/**
 * This function display and manage the edition mode for creating a new map for the game .
 * @param pRootWindow SDL_Surface An pointer to the main window .
 * @param menuChoice int An pointer to the variable menuChoice who allow to navigate between menu .
 */

void diplayEditionMode(SDL_Surface *pRootWindow, int *menuChoice){
    Difficulty lvlMode;
    int tmpChoice = 0;
    int nbObjectif = 0;
    int next = 0;
    int cursor = 1;
    char levelPath[A_HALF_FIFTY] = "";
    SDL_Surface sElem[MAP_MAX_SIZE] = {0};
    ELEMENT S_Elem[MAP_MAX_SIZE] = {0};
    Map mapCreated = {0, 0, 0, 0, "", ""};
    createMenu(pRootWindow, &tmpChoice, LVL_MENU_PATH);
    // get out F9 at chose and need to back menu 1
    if(tmpChoice == 0){
        return;
    }
    setDifficulty(tmpChoice, &lvlMode, levelPath);
    setNbObjectifByMode(lvlMode, &nbObjectif);
    cleanWindow(pRootWindow, 1);
    for(int i = 0; i < MAP_MAX_SIZE; i++) {
        setValueForMapToEdit(pRootWindow,  &sElem[i], &S_Elem[i], i, cursor);
    }
    SDL_Flip(pRootWindow);
    initMapStructForEdit(&mapCreated, lvlMode);
    while(tmpChoice != 0){

        next = editionEventManager(S_Elem, &cursor, &tmpChoice, &nbObjectif);
        cleanWindow(pRootWindow, 1);
        //cleanSurfaceEdit(sElem, MAP_MAX_SIZE);
        for(int i = 0; i < MAP_MAX_SIZE; i++){
            showChangeInMapEdit(pRootWindow, &sElem[i], &S_Elem[i]);
        }
        if(next != 0){

            cursor = next;
        }

        SDL_Flip(pRootWindow);
    }

    *menuChoice = 0;


}


/**
 * Set the number of objective is possible to create based on the difficulty selected .
 * @param lvlMode int A number to tell the difficulty chosen (0 = easy ...)
 */
void setNbObjectifByMode(int lvlMode, int *nbObjectif){
    switch(lvlMode){
        case 0:
            *nbObjectif = OBJ_EASY;
            break;
        case 1:
            *nbObjectif = OBJ_MEDIUM;
            break;
        case 2:
            *nbObjectif = OBJ_HARD;
            break;
        default:
            ;
    }
}

/**
 * Initialize the Element array to null value .
 * @param psElem ELEMENT An pointer to the array of Element .
 */
void initElementArray(ELEMENT *PS_Elem, int x, int y){
    int static numSurfaceForEdit = 0;
    PS_Elem->id = E_NULL;
    PS_Elem->block = 0;
    PS_Elem->numSurface = numSurfaceForEdit;
    PS_Elem->x = x;
    PS_Elem->y = y;
    PS_Elem->limitX = x + E_WIDTH;
    PS_Elem->limitY = y + E_HEIGHT;
    strcpy(PS_Elem->pathImg, "null");
    numSurfaceForEdit++;
}

/**
 * Check if the pathImage variable for an element is null and set them to green, aslo remove green in previous elements
 *  if is .
 * @param S_elem ELEMENT An pointer to the array of element structure .
 * @param current int A position of current element .
 * @parm next int A position of the next element .
 */
void checkAndUpdatePathElement(ELEMENT *S_elem, int current, int next){

    if(strcmp(S_elem[current].pathImg, "green") == 0){
        strcpy(S_elem[current].pathImg, "null");
    }
    if(strcmp(S_elem[next].pathImg, "null") == 0){
        strcpy(S_elem[next].pathImg, "green");
    }
}




//----------------------------------------------------------------------------------------------------------------------