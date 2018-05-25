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
#include "edition.h"
#include <time.h>
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
 * This function return the path for an image based on the num received .
 * @param numImage An number corresponding to the image selected .
 * @param pathImg A string where store the path .
 * @return char A letter representing the image in map .
 */
char getPathImage(int numImage, char pathImg[]){
    switch(numImage){
        case 0:
            strcpy(pathImg, "null");
            break;
        case 1:
            strcpy(pathImg, WALL_PATH);
            return E_WALL;
        case 2:
            strcpy(pathImg, BOX_PATH);
            return E_BOX;
        case 3:
            strcpy(pathImg, GOAL_PATH);
            return E_GOAL;
        case 4:
            strcpy(pathImg, MARIO_TOP_PATH);
            return E_MARIO_TOP;
        case 5:
            strcpy(pathImg, MARIO_RIGHT_PATH);
            return E_MARIO_RIGHT;
        case 6:
            strcpy(pathImg, MARIO_BOT_PATH);
            return E_MARIO_BOT;
        case 7:
            strcpy(pathImg, MARIO_LEFT_PATH);
            return E_MARIO_LEFT;
        default:
            ;
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
 * Initialize the Map structure with a first value .
 * @param editMap Map An pointer to currentMap variable .
 * @param difficulty A number corresponding to the difficulté chosen .
 */
void initMapStructForEdit(Map *pEditMap, int difficulty){
    srand(time(NULL));
    int num1 = rand();
    int num2 = rand();
    char name[A_HALF_HUNDR] = "";
    sprintf(name, "%dspe%d.txt", num1, num2);
    strcpy(pEditMap->name, name);
    pEditMap->number = 0;
    pEditMap->next = 0;
    pEditMap->previous = 0;
    pEditMap->difficulty = difficulty;
    for(int i = 0; i < A_HALF_THOUS; i++){
        pEditMap->content[i] = E_NULL;
    }
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
    int mapNum = 0;
    if(nbFile != 1){
        // multi
        while(stayIn){
            // first time
            if(current != -1){
                displayMap(&PS_tmpMap[current], sRootWindow, &current, menuChoice, 0);
            } else{
                // if current is -1 we need to get out while because menuChoice as been update
                stayIn = 0;
            }

        } // end while
    } else{
        //single
        displayMap(PS_tmpMap, sRootWindow, &current, menuChoice, 0);
    }
    if(menuChoice[2] != 0){
        // set mapNum
        mapNum = menuChoice[2] - 1;
        copyMap(MapToPlay, PS_tmpMap[mapNum]);
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

                (PS_tmpMap + i)->number = i + 1;
                (PS_tmpMap + i)->difficulty = -1;
                (PS_tmpMap + i)->previous = -1;
                (PS_tmpMap + i)->next = -1;

                for(int c = 0; c < A_HALF_HUNDR; c++){

                    (PS_tmpMap + i)->name[c] = 0;
                }
                for(int c = 0; c < MAP_MAX_SIZE; c++){
                    (PS_tmpMap + i)->content[c] = 0;

                }
            }
        }
        //----------------------------------------------
        // in bottom we try to init PS_tmpMap in a function but dont work we try to fix it later
        //initMap(PS_tmpMap, nbFile, fLvl);
        /* Here we can store the file data in PS_tmpMap*/
        setNameInMap(levelPath, E_TEXT, PS_tmpMap);
        setPreviousAndNext(PS_tmpMap, nbFile);
        for(int i = 0; i < nbFile; i++){
            setContentByFileName(levelPath, &PS_tmpMap[i]);
        }
        /* Now we can call the function to display the last menu */
        createMapMenu(pRootWindow, pMapToPlay, PS_tmpMap, pMenuChoice, nbFile);

    } else{
        // if no file in directory, we simply put value 0 in pMenuChoice[1] to get back menu2
        pMenuChoice[1] = 0;
    }
    // free memory
    free(PS_tmpMap);
}

/**
 * This function allow to navigate in the differents menu of selection .We have 3 menu :
 *  - menu 1 : He'll allow to chose between a playable mode or a map edition .
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
            cleanWindow(sRootWindow, 0);
        }

        /*manage the edition choice */
        if(menuChoice[0] == 2){
            // function management edition .
            diplayEditionMode(sRootWindow, &menuChoice[0]);
            /* here we try to display an image and allow to back to main menu with f9 key */
            //tmpShowEdition(sRootWindow, &menuChoice[0], EDITION_MENU_PATH);
            /* clean window */
            cleanWindow(sRootWindow, 0);
            continue;
        }

        /* second condition to display the second menu . */
        if(menuChoice[0] == 1 && menuChoice[1] == 0){
            /* if 0 we display the menu */
            createMenu(sRootWindow, &menuChoice[1], LVL_MENU_PATH);

            /*User have choosed an difficulty we can use it to define how much file the directory have .*/
            if(menuChoice[1] != 0){
                /* if different to 0 we can set a difficulty in lvlMode */
                setDifficulty(menuChoice[1], &LvlMode, levelPath);

            }else{
                /* if menu[1] is 0 we need to back to menu 1 */
                menuChoice[0] = 0;
                /* we clean the window */
                cleanWindow(sRootWindow, 0);
                continue;
            }
        } // end second condition

        cleanWindow(sRootWindow, 0);
        /* Menu3 condition*/
        if(menuChoice[0] == 1 && menuChoice[1] != 0 && menuChoice[2] == 0){
            /* Call the menu 3 manager function  */
            getMapData(sRootWindow, MapToPlay, menuChoice, levelPath, LvlMode);
        } else{
            // user have chose a map get back to main
            stayIn = 0;
        }
    } // end while
}


/**
 * check if mario is already in map and cannot be displayed another time .
 * @param S_elem ELEMENT An pointer to the array of element structure .
 * @param int The current position represented by cursor variable .
 * @return 1 if mario is already here 0 else .
 */
int checkIfMarioIsIn(ELEMENT *S_elem, int cursor){
    int tmpMario = 0;
    for(int i = 0; i < MAP_MAX_SIZE; i++){
        if(i == cursor){
            continue;
        }
        if(S_elem[i].id == E_MARIO_TOP || S_elem[i].id == E_MARIO_RIGHT || S_elem[i].id == E_MARIO_BOT || S_elem[i].id == E_MARIO_LEFT){
            tmpMario++;
        }
    }
    if(tmpMario >= 1){
        return 1;
    }
    return 0;
}


/**
 * check if objectives and box is already in map and cannot be displayed another time .
 * @param S_elem ELEMENT An pointer to the array of element structure .
 * @param nbObjectif int The number of objectives the map have depending a difficulty selected .
 * @return 1 if mario is already here 0 else .
 */
int checkIfObjIsHere(ELEMENT *S_elem, int nbObjectif){
    int tmpObj = 0;
    for(int i = 0; i < MAP_MAX_SIZE; i++){
        if(S_elem[i].id == E_GOAL){
            tmpObj++;
        }
    }
    if(tmpObj >= nbObjectif){
        return 1;
    }
    return 0;
}

/**
 * check if objectives and box is already in map and cannot be displayed another time .
 * @param S_elem ELEMENT An pointer to the array of element structure .
 * @param nbObjectif int The number of objectives the map have depending a difficulty selected .
 * @return 1 if mario is already here 0 else .
 */
int checkIfBoxIsHere(ELEMENT *S_elem, int nbObjectif){
    int tmpCaisse = 0;
    for(int i = 0; i < MAP_MAX_SIZE; i++){
        if(S_elem[i].id == E_BOX){
            tmpCaisse++;
        }
    }
    if(tmpCaisse >= nbObjectif){
        return 1;
    }
    return 0;
}


/**
 * Check and update the image is possible to diplay in relation with the presence of elements or not .
 * @param S_elem ELEMENT An pointer to the array of structure element .
 * @param nbObj int A number of objectives the mode have .
 * @param numImage An pointer to the variable numImage .
 * @param int The current element represented by cursor variable .
 */
void checkElementInEditMap(ELEMENT *S_elem, int nbObj, int *numImage, int cursor){
    if(!checkIfMarioIsIn(S_elem, cursor)){
        if(*numImage > 7){
            *numImage = 0;
        }
    } else{
        if(!checkIfObjIsHere(S_elem, nbObj) && !checkIfBoxIsHere(S_elem, nbObj)){
            if(*numImage > 3){
                *numImage = 0;
            }
            // box already here objectives not .
        } else if(checkIfBoxIsHere(S_elem, nbObj) && !checkIfObjIsHere(S_elem, nbObj)){
            if(*numImage > 3){
                *numImage = 0;
            } else if(*numImage == 2){
                // skip the box image
                *numImage = 3;
            }
        } else if(checkIfObjIsHere(S_elem, nbObj) && !checkIfBoxIsHere(S_elem, nbObj)){
            if(*numImage > 2){
                *numImage = 0;
            }
        } else{
            if(*numImage > 1){
                *numImage = 0;
            }
        }
    }

}

//----------------------------------------------------------------------------------------------------------------------
