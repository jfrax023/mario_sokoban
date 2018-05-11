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
        positionImg->x = sRoot->w / 2 - sImg->w / 2;
        positionImg->y = sRoot->h / 2 - sImg->h / 2;
    }
    SDL_BlitSurface(sImg, NULL, sRoot, positionImg);
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

//----------------------------------------------------------------------------------------------------------------------