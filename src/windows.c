/**
 * windows.c is a source file where we defined some function to manage any windows in this program .
 * Created by lilith on 08/05/2018
*/
#include <SDL.h>
#include <SDL_image.h>
#include "utilities.h"
#include <stdlib.h>
#include <stdio.h>



/**
 * Set a name and a background color to main window
 * @param sRootWindow SDL_Surface the main window
 */
void setNameAndBg(SDL_Surface *sRootWindow){
    SDL_WM_SetCaption(ROOT_WINDOW_NAME, NULL);
    SDL_FillRect(sRootWindow, NULL, SDL_MapRGB(sRootWindow->format, 255, 255, 255));
}

/**
 * Set an image in the main window according to the parameters passed in argument .
 * @param sRoot SDL_Surface the main window where blit image
 * @param sImg SDL_Surface a surface where the image is
 * @param positionImg SDL_Rect a sdl sturcture with a postion for image
 * @param center Bool 0 if no need to be center 1 else
 */
void setImageInWindow(SDL_Surface *sRoot, SDL_Surface *sImg, SDL_Rect *positionImg, int center){
    if(center != 0){
        positionImg->x = sRoot->w / 2 - sImg->w / 2;
        positionImg->y = sRoot->h / 2 - sImg->h / 2;
    }
    SDL_BlitSurface(sImg, NULL, sRoot, positionImg);
}