/**
 * events.c is a source file where we defined some function to manage events in this program .
 * Created by lilith on 10/05/18.
 */
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "utilities.h"
#include "game.h"

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

 // TMP REMOVE THEM LATER
 /* This code need to be in the edition fonctionnality*/
 int waitToBackEdition(){
     // var
     SDL_Event event;
     int again = 1;
     while(again){
         SDL_WaitEvent(&event);
         // wait a f9 event to back in main menu
         switch(event.type){
             case SDL_KEYDOWN:
                 switch(event.key.keysym.sym){
                     case SDLK_F9:
                         again = 0;
                         break;
                     default:
                         again = 1;
                         break;
                 } // end switch key
                 break;
             case SDL_QUIT:
                 SDL_Quit();
                 exit(EXIT_SUCCESS);
             default:
                 again = 1;
                 break;
         } // end switch type
     } // end while
     return 0;
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

 void gameEventManager(SDL_Surface *pRootWindow, SDL_Surface *sElem[], ELEMENT *elem, int numSurfaceMario){
     int inGame = 1;
     int nbObjClear = 0;
     int next = 0;
     int nextBox = 0;
     int current = numSurfaceMario;
     SDL_Event event;
     while(inGame){
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
                             setMovement(elem, pRootWindow, sElem, &current, &next, '-', NB_FRAME_IN_LINE, &nextBox);
                             break;
                         } else{
                             setMovement(elem, pRootWindow, sElem, &current, &next, '-', NB_FRAME_IN_LINE, &nextBox);
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
                             setMovement(elem, pRootWindow, sElem, &current, &next, '+', NB_FRAME_IN_LINE, &nextBox);
                             break;
                         } else{
                             setMovement(elem, pRootWindow, sElem, &current, &next, '+', NB_FRAME_IN_LINE, &nextBox);
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
                             setMovement(elem, pRootWindow, sElem, &current, &next, '+', 1, &nextBox);
                             break;
                         } else{
                             setMovement(elem, pRootWindow, sElem, &current, &next, '+', 1, &nextBox);
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
                             setMovement(elem, pRootWindow, sElem, &current, &next, '-', 1, &nextBox);
                             break;
                         } else{
                             setMovement(elem, pRootWindow, sElem, &current, &next, '-', 1, &nextBox);
                             break;
                         }
                     default:
                         continue;
                 }// end event.key...
             default:
                 ;
         } // end event.type
         //inGame = 0;
     }
}
































//----------------------------------------------------------------------------------------------------------------------