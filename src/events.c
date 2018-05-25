/**
 * events.c is a source file where we defined some function to manage events in this program .
 * Created by lilith on 10/05/18.
 */
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "utilities.h"
#include "game.h"
#include "windows.h"
#include "edition.h"
#include "windows.h"
#include "error_helper.h"
#include "file_helper.h"

//----------------------------------------------------------------------------------------------------------------------
/**
 * This function put the program in pause mode and wait an event SDL_QUIT .
 */
 void pause(){
    SDL_Event event;
    int again = 1;
    while(again){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                again = 0;
                break;
            default:
                again = 1;
                break;
        }
    }
 }

/**
 * This function allow to manage a keyboard event and recovery what the user have choose according to menu image .
 * The choices possible is defined by the parameter passed in argument and defined by the number of choice it is
 * possible to made in this menu like first menu have 2 possibilities and the second have 3 possibilities .
 * @param int pFlag An integer corresponding to the number of choice possible .
 * @return int The number choosed by user .
*/
 int getUserChoice(int pFlag){
     // var
    SDL_Event event;
    int again = 1;
    int choice = 0;
    // event while
    while(again){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                SDL_Quit();
                exit(EXIT_SUCCESS);
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_KP1:
                        choice = 1;
                        again = 0;
                        break;
                    case SDLK_KP2:
                        choice = 2;
                        again = 0;
                        break;
                    case SDLK_KP3:
                        // here we write a choice only if pflag is superior to 2
                        if(pFlag > 2){
                            choice = 3;
                            again = 0;
                        }
                        break;
                    // back to first menu
                    case SDLK_F9:
                        // we dont need activate this key in first menu because is a main menu and the backup is start
                        // only at the second menu .
                        if(pFlag > 2){
                            choice = 0;
                            again = 0;
                        }
                        break;
                    default:
                        again = 1;
                }// end switch
                break;
            default:
                again = 1;
        } // end switch
    }
    return choice;
 }


 /**
  * This function manage the choice made by the user and set the next step in current .
  * @param pMap An pointer to the map structure to access at next and previous var .
  * @param current int An pointer to the current variable used to move to the next step .
  */
void mapMenuEventManager(Map *pMap, int *current, int *menuChoice){
    int again = 1;
    SDL_Event event;
    while(again){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                SDL_Quit();
                exit(EXIT_SUCCESS);
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    // next map if possible
                    case SDLK_RIGHT:
                        if(pMap->next != -1){
                            *current = pMap->next;
                            again = 0;
                        }
                        break;
                    case SDLK_LEFT:
                        if(pMap->previous != -1){
                            *current = pMap->previous;
                            again = 0;
                        }
                        break;
                    case SDLK_F8:
                        menuChoice[1] = 0;
                        *current = -1;
                        again = 0;
                        break;
                    case SDLK_F9:
                        menuChoice[0] = 0;
                        menuChoice[1] = 0;
                        *current = -1;
                        again = 0;
                        break;
                    case SDLK_RETURN:
                        menuChoice[2] = pMap->number;
                        *current = -1;
                        again = 0;
                        break;
                    default:
                        again = 1;
                        break;
                } // end keydown
                break;
            default:
                again = 1;
        } // end event type
    } // end again
 }

/**
 * Juste wait a return event to start game in main
 */
void gameStartEvent(){
     SDL_Event event;
     int again = 1;
     while(again){
         SDL_WaitEvent(&event);
         switch(event.type){
             case SDL_QUIT:
                 SDL_Quit();
                 exit(EXIT_SUCCESS);
             case SDL_KEYDOWN:
                 switch(event.key.keysym.sym){
                     case SDLK_RETURN:
                         again = 0;
                         break;
                     default:
                         continue;
                 }
             default:
                 continue;
         }
     }
 }

 /**
  * Event manager for game event .
  * @param pRootWindow SDL_Surface An pointer to the main window .
  * @param sElem SDL_Surface An pointer to an array of surface corresponding to elements surface .
  * @param elem ELEMENT An pointer to the array of Element structure .
  * @param numSurfaceMario int The position of mario in map .
  */
 void gameEventManager(SDL_Surface *pRootWindow, SDL_Surface *sElem[], ELEMENT *elem, int numSurfaceMario){
     int inGame = 1;
     int nbObjClear = getNbObjectif(NULL);
     int next = 0;
     int nextBox = 0;
     int current = numSurfaceMario;
     SDL_Event event;
     while(inGame && nbObjClear != 0){

         SDL_WaitEvent(&event);
         switch(event.type){
             case SDL_QUIT:
                 for(int i = 0; i < MAP_MAX_SIZE; i++){
                     SDL_FreeSurface(sElem[i]);
                 }
                 SDL_Quit();
                 exit(EXIT_SUCCESS);
             case SDL_KEYDOWN:
                 switch(event.key.keysym.sym){
                     case SDLK_UP:
                         next = setNextTarget(current , NB_FRAME_IN_LINE, '-');
                         nextBox = checkMovement(next, elem, NB_FRAME_IN_LINE, '-');
                         // next box can contain 0 if movement impossible, 1 if movement possible, position of the next surface after
                         //  a box if box there .
                         if(!nextBox){
                             continue;
                         } else if(nextBox == 1){
                             // we push box need to know the possition after here
                             nextBox = 0;
                             setMovement(elem, pRootWindow, sElem, &current, &next, '-', NB_FRAME_IN_LINE, &nextBox, &nbObjClear);
                             break;
                         } else{
                             setMovement(elem, pRootWindow, sElem, &current, &next, '-', NB_FRAME_IN_LINE, &nextBox, &nbObjClear);
                             break;
                         }
                     case SDLK_DOWN:
                         next = setNextTarget(current , NB_FRAME_IN_LINE, '+');
                         nextBox = checkMovement(next, elem, NB_FRAME_IN_LINE, '+');
                         if(!nextBox){
                             continue;
                         } else if(nextBox == 1){
                             // we push box need to know the possition after here
                             nextBox = 0;
                             setMovement(elem, pRootWindow, sElem, &current, &next, '+', NB_FRAME_IN_LINE, &nextBox, &nbObjClear);
                             break;
                         } else{
                             setMovement(elem, pRootWindow, sElem, &current, &next, '+', NB_FRAME_IN_LINE, &nextBox, &nbObjClear);
                             break;
                         }
                     case SDLK_RIGHT:
                         next = setNextTarget(current , 1, '+');
                         nextBox = checkMovement(next, elem, 1, '+');
                         if(!nextBox){
                             continue;
                         } else if(nextBox == 1){
                             // we push box need to know the possition after here
                             nextBox = 0;
                             setMovement(elem, pRootWindow, sElem, &current, &next, '+', 1, &nextBox, &nbObjClear);
                             break;
                         } else{
                             setMovement(elem, pRootWindow, sElem, &current, &next, '+', 1, &nextBox, &nbObjClear);
                             break;
                         }
                     case SDLK_LEFT:
                         next = setNextTarget(current , 1, '-');
                         nextBox = checkMovement(next, elem, 1, '-');
                         if(!nextBox){
                             continue;
                         } else if(nextBox == 1){
                             // we push box need to know the possition after here
                             nextBox = 0;
                             setMovement(elem, pRootWindow, sElem, &current, &next, '-', 1, &nextBox, &nbObjClear);
                             break;
                         } else{
                             setMovement(elem, pRootWindow, sElem, &current, &next, '-', 1, &nextBox, &nbObjClear);
                             break;
                         }
                     case SDLK_F9:
                         inGame = 0;
                     default:
                         continue;
                 }// end event.key...
             default:
                 ;
         } // end event.type

     } // End main while

}

/**
 * Event manager for edition mode .
 * @param pRootWindow SDL_Surface An pointer to the main window .
 * @param sElem SDL_Surface An pointer to an array of surface corresponding to elements surface .
 * @param elem ELEMENT An pointer to the array of Element structure .
 * @param cursor int An pointer to the variable cursor representing the current position or element where we work .
 * @param tmpChoice int An pointer on the variable tmpChoice to tell continue or get out while .
 * @param nbObj int An pointer on the variable nbObjectif .
 */
int editionEventManager(ELEMENT elem[], int *cursor, int *tmpChoice, int *nbObj, Map *mapCreated, char levelPath[]){

    SDL_Event event;
    int again = 1;
    int static numImage = 0;
    int error = 0;
    int next = 0;
    char debugPaht[200] = "";
    while(again){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                SDL_Quit();
                exit(EXIT_SUCCESS);
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_LEFT:
                        // check if we can access to left
                        if(!setNextForEdit(*cursor, 1, '-'))
                            continue;
                        // set next target
                        next = setNextForEdit(*cursor, 1, '-');
                        // change a color if just white frame
                        checkAndUpdatePathElement(elem, *cursor, next);
                        numImage = 0;
                        return  next;
                    case SDLK_RIGHT:
                        if(!setNextForEdit(*cursor, 1, '+'))
                            continue;
                        next = setNextForEdit(*cursor, 1, '+');
                        checkAndUpdatePathElement(elem, *cursor, next);
                        numImage = 0;
                        return next;
                    case SDLK_UP:
                        if(!setNextForEdit(*cursor, NB_FRAME_IN_LINE, '-'))
                            continue;
                        next = setNextForEdit(*cursor, NB_FRAME_IN_LINE, '-');
                        checkAndUpdatePathElement(elem, *cursor, next);
                        numImage = 0;
                        return next;
                    case SDLK_DOWN:
                        if(!setNextForEdit(*cursor, NB_FRAME_IN_LINE, '+'))
                            continue;
                        next = setNextForEdit(*cursor, NB_FRAME_IN_LINE, '+');
                        checkAndUpdatePathElement(elem, *cursor, next);
                        numImage = 0;
                        return next;
                    case SDLK_SPACE:
                        /* we have 7 image to display but if mario is already displayed we use only
                         the three first image (wall, obj, caisse) and then the user have placed nbObjectives and boxes
                         we remove them too .
                         */
                        checkElementInEditMap(elem, *nbObj, &numImage, *cursor);
                        if((numImage) == 0){
                            // the case 0 is a white frame so we set elem[*cursor].id to " " and pathImg to null
                            elem[*cursor].id = E_NULL;
                            strcpy(elem[*cursor].pathImg, "null");
                            numImage++;
                            return -1;

                        } else{
                            // update the two interesting variable in elem .
                            elem[*cursor].id = getPathImage(numImage, elem[*cursor].pathImg);
                            numImage++;
                            return -1;
                        }
                    case SDLK_F9:
                        again = 0;
                        *tmpChoice = 0;
                        break;
                    case SDLK_F10:
                        // here need to save new map but only if completed
                        if(!checkIfMapIsCorrect(elem, *nbObj))
                            continue;
                        if(!checkIfBorderIsCorrect(elem))
                            continue;
                        if(!checkNumberOfFreeCase(elem))
                            continue;
                        if(checkFileNameInDir(levelPath, mapCreated->name))
                            continue;
                        saveMapInDir(levelPath, mapCreated->name, elem, "w+");
                        *tmpChoice = 0;
                        return -1;
                    default:
                        continue;
                }
            default:
                continue;
        }
    }

 }
































//----------------------------------------------------------------------------------------------------------------------