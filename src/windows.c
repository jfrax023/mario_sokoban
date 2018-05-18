/**
 * windows.c is a source file where we defined some function to manage any windows in this program .
 * Created by lilith on 08/05/2018 .
*/
#include <SDL.h>
#include <SDL_image.h>
#include "utilities.h"
#include <stdlib.h>
#include <stdio.h>
#include "error_helper.h"
#include "events.h"
#include <string.h>

//----------------------------------------------------------------------------------------------------------------------
/**
 * Set a name and a background color to main window .
 * @param sRootWindow SDL_Surface The main window .
 */
void setNameAndBg(SDL_Surface *sRootWindow){
    SDL_WM_SetCaption(ROOT_WINDOW_NAME, NULL);
    SDL_FillRect(sRootWindow, NULL, SDL_MapRGB(sRootWindow->format, 255, 255, 255));
}

/**
 * This function clean the current main window by recoloring and flip them .
 * @param sWindow SDL_Surface The main window .
 * @param color int Array with rgb color [r, g, b] nedded .
 * @param flipFlag int A flag corresponding to tell if we need to SDL_Flip this surface or not, 0 dont flip 1 flip .
 */
void cleanWindow(SDL_Surface *sWindow, int color[], int flipFlag){
    SDL_FillRect(sWindow, NULL, SDL_MapRGB(sWindow->format, color[0], color[1], color[2]));
    if(flipFlag == 1){
        // update window
        SDL_Flip(sWindow);
    }
}

/**
 * Set an image in the main window according to the parameters passed in argument .
 * @param sRoot SDL_Surface The main window where blit image .
 * @param sImg SDL_Surface A surface where the image is .
 * @param positionImg SDL_Rect A sdl sturcture with a postion for image .
 * @param center Bool 0 if no need to be center 1 else .
 */
void setImageInWindow(SDL_Surface *sRoot, SDL_Surface *sImg, SDL_Rect *positionImg, int center){
    if(center != 0){
        positionImg->x = (sRoot->w / 2) - ( sImg->w / 2);
        positionImg->y = (sRoot->h / 2) - (sImg->h / 2);
    }
    SDL_BlitSurface(sImg, NULL, sRoot, positionImg);
}


/**
 * Blit an image already put in sElement to the main window .
 * @param sElement SDL_Surface The current surface where we work .
 * @param sRootWindow SDL_Surface The main window .
 * @param position SDL_Rect The position of this surface .
 */
void setImgToFrame(SDL_Surface *sElement, SDL_Surface *sRootWindow, SDL_Rect *position){
    SDL_BlitSurface(sElement, NULL, sRootWindow, position);
    // add new x position
    position->x += E_WIDTH;
}

/**
 * Create a séléction menu corresponding to one surface where we put a menu image and "blit" them
 *  in the main window .After that she call the event function who will wait to get an user choice .
 * @param sRootWindow SDL_Surface The main window .
 * @param pUserMenuChoice int One pointer on userMenuChoice variable located in main function .
 * @param imgPath char The path to access to image .
 */
void createMenu(SDL_Surface *sRootWindow, int *pUserMenuChoice, char imgPath[]){
    // var and other
    SDL_Surface *sImgMenu = NULL;
    SDL_Rect imgMenuPosition;
    int possibilities = 0;
    /* we check the imgPath to define how much possibilities is possible only 2 or 3 is possible and corresponding to
        the menu image possibilities menu = 2, level menu = 3
     */
    if(strcmp(imgPath, MENU_PATH) == 0){
        possibilities = 2;
    } else{
        possibilities = 3;
    }
    // create menu surface
    sImgMenu = IMG_Load(imgPath);
    checkIfSurfaceIsNull(sImgMenu, "Image not found ");


    // put menu image to sImgMenu surface
    setImageInWindow(sRootWindow, sImgMenu, &imgMenuPosition, 1);
    // update window
    SDL_Flip(sRootWindow);
    *pUserMenuChoice = getUserChoice(possibilities);
    // free memory
    SDL_FreeSurface(sImgMenu);
}

/**
 * This function receive a map in parameter and translate them to an SDL window .
 * @param pMap Map An pointer to the map structure where is stored the map data .
 * @param pRootWindow SDL_Surface An pointer to main window .
 * @param current int An pointer to the variable current to manage while .
 * @param pMenuChoice int An pointer to the array menuChoice .
 * @param inGame in Bool 0 tell not in game 1 game is started .
 */
void displayMap(Map *pMap, SDL_Surface *pRootWindow, int *current, int *pMenuChoice, int inGame){
    // content size
    int size = (int) strlen(pMap->content);
    int color[3] = {255, 255, 255};
    SDL_Rect positionElement = {0, 0};
    // MAP_MAX_SIZE corresponding to the number of frame we have in map (16 * 16) = 256
    SDL_Surface *sElement[MAP_MAX_SIZE] = {NULL};
    // surface counter to avoid end line case (i have 16 \n more than nS)
    int nS = 0;

    for(int i = 0; i < size; i++){
        switch(pMap->content[i]){
            case E_WALL:
                sElement[nS] = IMG_Load(WALL_PATH);
                setImgToFrame(sElement[nS], pRootWindow, &positionElement);
                nS++;
                break;
            case E_BOX:
                sElement[nS] = IMG_Load(BOX_PATH);
                setImgToFrame(sElement[nS], pRootWindow, &positionElement);
                nS++;
                break;
            case E_BOX_OK:
                sElement[nS] = IMG_Load(BOX_OK_PATH);
                setImgToFrame(sElement[nS], pRootWindow, &positionElement);
                nS++;
                break;
            case E_GOAL:
                sElement[nS] = IMG_Load(GOAL_PATH);
                setImgToFrame(sElement[nS], pRootWindow, &positionElement);
                nS++;
                break;
            case E_MARIO_TOP:
                sElement[nS] = IMG_Load(MARIO_TOP_PATH);
                setImgToFrame(sElement[nS], pRootWindow, &positionElement);
                nS++;
                break;
            case E_MARIO_BOT:
                sElement[nS] = IMG_Load(MARIO_BOT_PATH);
                setImgToFrame(sElement[nS], pRootWindow, &positionElement);
                nS++;
                break;
            case E_MARIO_LEFT:
                sElement[nS] = IMG_Load(MARIO_LEFT_PATH);
                setImgToFrame(sElement[nS], pRootWindow, &positionElement);
                nS++;
                break;
            case E_MARIO_RIGHT:
                sElement[nS] = IMG_Load(MARIO_RIGHT_PATH);
                setImgToFrame(sElement[nS], pRootWindow, &positionElement);
                nS++;
                break;
            case E_NULL:
                // here just change the position of element .
                positionElement.x += E_WIDTH;
                nS++;
                break;
            case E_END_LINE:
                // end line tell to change the y offset to move to the next line
                positionElement.y += E_HEIGHT;
                positionElement.x = 0;
                break;
            default:
                fprintf(stderr, "Warning this character is not handled => %c", pMap->content[i]);
                break;
        } // end switch

    } // end for

    SDL_Flip(pRootWindow);
    if(inGame){
        // call event manger for game event
    } else{
        // call event manager to define the next step in menu functionality
        mapMenuEventManager(pMap, current, pMenuChoice);
    }
    // clean
    cleanWindow(pRootWindow, color, 1);
    // free surface
    for(int i = 0; i < MAP_MAX_SIZE; i++){
        SDL_FreeSurface(sElement[i]);
    }

}

void tmpShowEdition(SDL_Surface *sRootWindow, int *pUserChoice, char imgPath[]){
    SDL_Surface *sImgMenu = NULL;
    SDL_Rect imgMenuPosition;

    // create menu surface
    sImgMenu = IMG_Load(imgPath);
    checkIfSurfaceIsNull(sImgMenu, "Image not found ");

    // put menu image to sImgMenu surface
    setImageInWindow(sRootWindow, sImgMenu, &imgMenuPosition, 1);
    // update window
    SDL_Flip(sRootWindow);

    // wait to back to menu 1
    *pUserChoice = waitToBackEdition();
    // free memory
    SDL_FreeSurface(sImgMenu);
}

//----------------------------------------------------------------------------------------------------------------------