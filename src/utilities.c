/**
 * utilities.c is a source file where we define utilities functions .This functions is global use and not in relation
 *  with a specific functionnalities .
 *  Created by lilith on 14/05/18.
 */

#include <stdlib.h>
#include <stdio.h>
#include "utilities.h"
#include <string.h>
#include <SDL/SDL.h>
#include "windows.h"
#include "file_helper.h"

//----------------------------------------------------------------------------------------------------------------------

/**
 * This function set the difficulty mode the user have choose and define the path to access to the directory where
 *  maps as stored .
 * @param userChoice int The number corresponding to the difficulty associated in menu .
 * @param LvlMode Difficulty An enumeration representing the current difficulty .
 * @param lvlPath char The path where we can found the 'map' representation in a file .
 */
void setDifficulty(int userChoice, Difficulty *LvlMode, char lvlPath[]){
    switch(userChoice){
        case 1:
            *LvlMode = EASY;
            strcpy(lvlPath, LEVEL_EASY_DIR);
            break;
        case 2:
            *LvlMode = MEDIUM;
            strcpy(lvlPath, LEVEL_MEDIUM_DIR);
            break;
        case 3:
            *LvlMode = HARD;
            strcpy(lvlPath, LEVEL_HARD_DIR);
            break;
        default:
            *LvlMode = EASY;
            strcpy(lvlPath, LEVEL_EASY_DIR);
            break;
    }
}

/**
 * This function set value to previous an next variable to the map structure .
 * @param map Map An pointer to the first structure Map .
 * @param nbFile int The number of file found in directory .
 */
void setPreviousAndNext(Map *map,int  nbFile){
    // if just one map we set to -1
    if(nbFile == 1){
        map->previous = -1;
        map->next = -1;
    }else{
        for(int i = 0; i < nbFile; i++){
            if(i == 0){
                map[i].previous = -1;
                continue;
            }
            map[i-1].next = i;
            map[i].previous = i - 1;
        }
    }
}

/**
 * Copy one map structure to another
 * @param MapToPlay Map An pointer on the destination .
 * @param copy Map The map to copy .
 */
void copyMap(Map *MapToPlay, Map copy){
    MapToPlay->number = copy.number;
    MapToPlay->difficulty = copy.difficulty;
    MapToPlay->previous = -1;
    MapToPlay->next = -1;
    strcpy(MapToPlay->name, copy.name);
    strcpy(MapToPlay->content, copy.content);
}


/**
 * This function is a manger for the third menu .She create a while where we can move in menu to chose a map for play.
 * @param sRootWindow SDL_Surface An pointer on the main window .
 * @param MapToPlay Map An pointer to the final map structure wher we will store the map the user have chosen .
 * @param PS_tmpMap Map An pointer on the first adress corresponding to the first map strored in this structure .
 * @param menuChoice int An pointer to the array menuChoice .
 * @param nbFile  int The number of file we have found in directory corresponding to the difficulty chosen .
 */
void createMapMenu(SDL_Surface *sRootWindow, Map *MapToPlay, Map *PS_tmpMap, int *menuChoice, int nbFile){
    int current = 0;
    int stayIn = 1;
    if(nbFile != 1){
        // multi
        while(stayIn){
            // first time
            // IN PROGRESS

            stayIn = 0;
        } // end while
    } else{
        //single
    }
}


/**
 * This function define an array of Map structure to store the data corresponding to an map located in a file .After
 *  she create this array she call  functions to set a différents variable in like a name and content .After that we
 *  can call the function to display a third menu with the data we have stored in this array .
 * @param pRootWindow SDL_Surface An pointer to main window .
 * @param pMapToPlay Map An pointer to the Map structure where we will storing the map the user have chose .
 * @param pMenuChoice int An pointer to the array where we store the choice made by user .
 * @param levelPath char The path where search map
 * @param fLvl int The difficulty chosen by user .
 */
void getMapData(SDL_Surface *pRootWindow, Map *pMapToPlay, int *pMenuChoice, char levelPath[], int fLvl){
    int nbFile = 0;
    Map *PS_tmpMap = NULL;

    // get number of file
    nbFile = getNbFileInDir(levelPath, E_TEXT);
    if(nbFile != 0){
        /* Create array of Map structure */
        PS_tmpMap = malloc(nbFile * sizeof(Map));
        if(PS_tmpMap == NULL){
            fprintf(stderr, "Allocation memory failed !!");
            SDL_Quit();
            exit(EXIT_FAILURE);
        }
        /* REMOVE THEM LATER IF POSSIBLE*/
        // init value to 0
        //---------------------------------------------
        if(nbFile == 1){
            PS_tmpMap->number = 1;
            PS_tmpMap->difficulty = fLvl;
            PS_tmpMap->previous = -1;
            PS_tmpMap->next = -1;
            for (int i = 0; i < A_HALF_HUNDR; ++i) {
                PS_tmpMap->name[i] = 0;
            }
            for (int j = 0; j < MAP_MAX_SIZE; ++j) {
                PS_tmpMap->content[j] = 0;
            }
        } else{
            for(int i = 0; i < nbFile; i++){
                PS_tmpMap[i].number = i + 1;
                PS_tmpMap[i].difficulty = fLvl;
                PS_tmpMap[i].previous = -1;
                PS_tmpMap[i].next = -1;
                for(int c = 0; c < A_HALF_HUNDR; c++){
                    PS_tmpMap[i].name[c] = 0;
                }
                for(int c = 0; c < MAP_MAX_SIZE; c++){
                    PS_tmpMap[i].content[c] = 0;
                }
            }
        }
        //----------------------------------------------
        // in bottom we try to init PS_tmpMap in a function but dont work we try to fix it later
        //initMap(PS_tmpMap, nbFile, fLvl);
        /* Here we can store the file data in PS_tmpMap*/
        setNameInMap(levelPath, E_TEXT, PS_tmpMap);
        setContentByFileName(levelPath, PS_tmpMap);
        setPreviousAndNext(PS_tmpMap, nbFile);
        /* Now we can call the function to display the last menu */
        createMapMenu(pRootWindow, pMapToPlay, PS_tmpMap, pMenuChoice, nbFile);

        /*
         * Wait until menu 3 as been displayed and user have chosen a map . IN PROGRESS
        */

    } else{
        // if no file in directory, we simply put value 0 in pMenuChoice[1] to get back menu2
        pMenuChoice[1] = 0;
    }
    // gestion menu3
    
    free(PS_tmpMap);
}

/**
 * This function display allow to navigate in the differents menu of selection .We have 3 menu :
 *  - menu 1 : He'll allow to choose between a playable mode or to map editon .
 *  - menu 2 : Allow to choose the difficulty for the game .Easy, medium, hard .More higher is a choice more difficult the
 *              map is
 *  - menu 3 : Display a map and allow to navigate to the next or the previous map if possible, and select them .
 *  also allows you to move between the menus with specific key (F9 = first menu, F8 = second menu) .
 * @param sRootWindow SDL_Surface The main window where display menu
 * @param MapToPlay Map One pointer to the Map structure we will store the map chosen by user .
 */
void showMenuAndSelectMap(SDL_Surface *sRootWindow, Map *MapToPlay){
    /* var and pointers etc ... */
    int menuChoice[3] = {0};
    int aBgColor[] = {255, 255, 255};
    int stayIn = 1;
    char levelPath[A_HALF_FIFTY] = "";
    Difficulty LvlMode = EASY;

    /* Main while*/
    while(stayIn){
        /* first condition to display the first menu */
        if(menuChoice[0] == 0){
            /* if menuChoice is 0 we display the first menu */
            createMenu(sRootWindow, &menuChoice[0], MENU_PATH);
            /* we clean window but dont flip them at the moment */
            cleanWindow(sRootWindow, aBgColor, 0);
        }

        /*manage the edition choice */
        if(menuChoice[0] == 2){
            /* here we try to display an image and allow to back to main menu with f9 key */
            tmpShowEdition(sRootWindow, &menuChoice[0], EDITION_MENU_PATH);
            /* clean window */
            cleanWindow(sRootWindow, aBgColor, 1);
        }

        /* second condition to display the second menu . */
        if(menuChoice[0] == 1 && menuChoice[1] == 0){
            /* if 0 we display the menu */
            createMenu(sRootWindow, &menuChoice[1], LVL_MENU_PATH);

            /*User have choosed an difficulty we can use it to define how much file the directory have .*/
            if(menuChoice[1] != 0){
                /* if different to 0 we can set a difficulty in lvlMode */
                setDifficulty(menuChoice[1], &LvlMode, levelPath);
                // DONT FORGOT TO REMOVE
                stayIn = 0;
            }else{
                /* if menu[1] is 0 we need to back to menu 1 */
                menuChoice[0] = 0;
                /* we clean the window */
                cleanWindow(sRootWindow, aBgColor, 1);
                continue;
            }
        } // end second condition

        cleanWindow(sRootWindow, aBgColor, 1);
        /* Menu3 condition*/
        if(menuChoice[0] == 1 && menuChoice[1] != 0 && menuChoice[2] == 0){
            /* Call the menu 3 manager function  */
            getMapData(sRootWindow, MapToPlay, menuChoice, levelPath, LvlMode);
        }
    } // end while
}

//----------------------------------------------------------------------------------------------------------------------
