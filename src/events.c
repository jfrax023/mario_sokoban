/**
 * events.c is a source file where we defined some function to manage events in this program .
 * Created by lilith on 10/05/18.
 */
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

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
 * possible to make in this menu like first menu have 2 possibilities and the second have 3 possibilities .
 * @param int pFlag An integer corresponding to the number of choice possible .
 * @return int The number choosed by user .
*/
 int getUserChoice(int pFlag){
     // var
    SDL_Event event;
    int again = 1;
    int choice = 0;
    int test = 0;
    // event while
    while(again){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                SDL_Quit();
                exit(EXIT_SUCCESS);
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_KP1:
                        test = event.key.keysym.sym;
                        choice = 1;
                        again = 0;
                        break;
                    case SDLK_KP2:
                        choice = 2;
                        again = 0;
                        break;
                    case SDLK_KP3:
                        // here we write a choice only if pflag is superior
                        if(pFlag > 2){
                            choice = 3;
                            again = 0;
                        }
                        break;
                    default:
                        again = 1;
                }// end switch
                break;

        } // end switch
    }
    return choice;
 }
