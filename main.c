#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "events.h"
#include "utilities.h"
#include "windows.h"
#include "error_helper.h"


int main(int argc, char *argv[]) {
    // variable definition
    SDL_Surface *sRootWindow = NULL;
    SDL_Surface *sImgMenu = NULL;
    SDL_Rect imgMenuPosition;

    // Initialisation de SDL
    SDL_Init(SDL_INIT_VIDEO);

    /* Main window creation*/
    SDL_WM_SetIcon(IMG_Load(BOX_PATH), NULL);

    sRootWindow = SDL_SetVideoMode(ROOT_WINDOW_WIDTH, ROOT_WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    // check
    checkIfSurfaceIsNull(sRootWindow, "Cannot create window ");
    /* End main window creation ca use this after*/
    // create menu surface
    sImgMenu = IMG_Load(MENU_PATH);
    checkIfSurfaceIsNull(sImgMenu, "Image not found ");

    // set a bg color and a name to the main window
    setNameAndBg(sRootWindow);
    // Center the menu and blit him
    // set img of menu to sImgMenu surface
    setImageInWindow(sRootWindow, sImgMenu, &imgMenuPosition, 1);
    // update window
    SDL_Flip(sRootWindow);

    // pause
    pause();
    // free memory
    SDL_FreeSurface(sImgMenu);
    SDL_Quit();
    return EXIT_SUCCESS;
}