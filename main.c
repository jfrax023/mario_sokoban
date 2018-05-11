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
    //SDL_Surface *sImgMenu = NULL;
    int userMenuChoice = 0;
    int aBgColor[] = {255, 255, 255};
    //SDL_Rect imgMenuPosition;

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
    createMenu(sRootWindow, &userMenuChoice, MENU_PATH);
    // we clean window but dont flip them at the moment
    cleanWindow(sRootWindow, aBgColor, 0);

    // The first menu as been displayed and the user have choose now we can move to the second menu or on edition level
    if(userMenuChoice == 1){
        /* seconde menu*/
        // remove value of userMenuChoice because we reuse it
        userMenuChoice = 0;
        createMenu(sRootWindow, &userMenuChoice, LVL_MENU_PATH);
    } else{
        /* edition*/
        SDL_Quit();
        exit(EXIT_SUCCESS);
    }
    cleanWindow(sRootWindow, aBgColor, 1);
    /*      END MENU SELECTION      */

    /*
     MAP CODE
     */

    pause();

    SDL_Quit();
    return EXIT_SUCCESS;
}