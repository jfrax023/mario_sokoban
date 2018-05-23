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

    int aBgColor[] = {255, 255, 255};
    int startGame = 0;
    // here we define one map we will contains the map choosed by user .
    Map MapToPlay = {0, 0, 0, 0, "", ""};

    // Initialisation de SDL
    SDL_Init(SDL_INIT_VIDEO);

    /* Main window creation*/
    SDL_WM_SetIcon(IMG_Load(BOX_PATH), NULL);

    sRootWindow = SDL_SetVideoMode(ROOT_WINDOW_WIDTH, ROOT_WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    // check
    checkIfSurfaceIsNull(sRootWindow, "Cannot create window ");
    /* End main window creation ca use this after*/

    // set a bg color and a name to the main window
    setNameAndBg(sRootWindow);
    /*      START WHILE MENU        */

    showMenuAndSelectMap(sRootWindow, &MapToPlay);

    cleanWindow(sRootWindow, 1);
    // here normally we have a map data to play .
    showOverlay(sRootWindow);

    displayMap(&MapToPlay, sRootWindow, NULL, NULL, 1);
    pause();

    SDL_Quit();
    return EXIT_SUCCESS;
}