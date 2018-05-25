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
#include "game.h"
#include "edition.h"
#include "windows.h"

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
void cleanWindow(SDL_Surface *sWindow, int flipFlag){
    SDL_FillRect(sWindow, NULL, SDL_MapRGB(sWindow->format, 255, 255, 255));
    if(flipFlag == 1){
        // update window
        SDL_Flip(sWindow);
    }
}


/**
 * This function update the current map with a new image of an element chosen by user .
 * @param pRootWindow SDL_Surface The main window .
 * @param psElem SDL_Surface An pointer to the surface array corresponding to the elements of the game .
 * @param PS_Elem ELEMENT An pointer to the array of structure element .
 * @param currentFlag int the current surface to update .
 * @param cursor An pointer to the variable cursor to representing the current elements where we work .
 * @param img A number who tell what the image we need to display .
 */
void showChangeInMapEdit(SDL_Surface *pRootWindow, SDL_Surface *psElem, ELEMENT *PS_Elem){
    // clean

    SDL_Rect posElem;
    posElem.x = 0;
    posElem.y = 0;

    //for(int i = 0; i < MAP_MAX_SIZE; i++){
    if(strcmp(PS_Elem->pathImg, "null") == 0){
        // create surface
        psElem = SDL_CreateRGBSurface(SDL_HWSURFACE, E_WIDTH, E_HEIGHT, 32, 0, 0, 0, 0);
        checkIfSurfaceIsNull(psElem, "Surface is null .");
        // position
        posElem.x = (u_int16_t) PS_Elem->x;
        posElem.y = (u_int16_t) PS_Elem->y;
        // set value
        SDL_FillRect(psElem, NULL, SDL_MapRGB(pRootWindow->format, 255, 255, 255));
        SDL_BlitSurface(psElem, NULL, pRootWindow, &posElem);
        return;

    } else if(strcmp(PS_Elem->pathImg, "green") == 0){

        psElem = SDL_CreateRGBSurface(SDL_HWSURFACE, E_WIDTH, E_HEIGHT, 32, 0, 0, 0, 0);
        checkIfSurfaceIsNull(psElem, "Surface is null .");

        posElem.x = (u_int16_t) PS_Elem->x;
        posElem.y = (u_int16_t) PS_Elem->y;


        SDL_FillRect(psElem, NULL, SDL_MapRGB(pRootWindow->format, 93, 206, 68));
        SDL_BlitSurface(psElem, NULL, pRootWindow, &posElem);
        return;
    }

    posElem.x = (u_int16_t) PS_Elem->x;
    posElem.y = (u_int16_t) PS_Elem->y;

    psElem = IMG_Load(PS_Elem->pathImg);
    checkIfSurfaceIsNull(psElem, "Surface is null .");


    setImageInWindow(pRootWindow, psElem, &posElem, 0);


}

/**
 * This function display the map who will be editing by the user .Actually is just a white surface end one green surface
 *  representing the cursor where we work .
 * @param pRootWindow SDL_Surface The main window .
 * @param psElem SDL_Surface An pointer to the surface array corresponding to the elements of the game .
 * @param PS_Elem ELEMENT An pointer to the array of structure element .
 * @param cursor int An pointer to the variable cursor to representing the current elements where we work .
 */
void setValueForMapToEdit(SDL_Surface *pRootWindow, SDL_Surface *psElem, ELEMENT *PS_Elem,
                          int currentFlag, int cursor){
    SDL_Rect positionSurface;

    psElem = SDL_CreateRGBSurface(SDL_HWSURFACE, E_WIDTH, E_HEIGHT, 32, 0, 0, 0, 0);
    checkIfSurfaceIsNull(psElem, "Surface is null");
    if(currentFlag == cursor){
        positionSurface.y = 0;
        positionSurface.x = 0;
        SDL_FillRect(psElem, NULL, SDL_MapRGB(pRootWindow->format, 93, 206, 68));
        SDL_BlitSurface(psElem, NULL, pRootWindow, &positionSurface);
        initElementArray(PS_Elem, positionSurface.x, positionSurface.y);
        positionSurface.x += E_WIDTH;
        return;
    }
    // change line need update y
    if(currentFlag % (NB_FRAME_IN_LINE) == 0){
        positionSurface.x = 0;
        positionSurface.y += E_HEIGHT;
        SDL_FillRect(psElem, NULL, SDL_MapRGB(pRootWindow->format, 255, 255, 255));
        SDL_BlitSurface(psElem, NULL, pRootWindow, &positionSurface);
        initElementArray(PS_Elem, positionSurface.x, positionSurface.y);
        return;
    }
    SDL_FillRect(psElem, NULL, SDL_MapRGB(pRootWindow->format, 255, 255, 255));
    SDL_BlitSurface(psElem, NULL, pRootWindow, &positionSurface);
    initElementArray(PS_Elem, positionSurface.x, positionSurface.y);
    positionSurface.x += E_WIDTH;
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
        positionImg->x = (u_int16_t) ((sRoot->w / 2) - ( sImg->w / 2));
        positionImg->y = (u_int16_t) ((sRoot->h / 2) - (sImg->h / 2));
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
    int numSurfaceMario = 0;
    SDL_Rect positionElement = {0, 0};
    SDL_Rect positionMario = {0, 0};
    // MAP_MAX_SIZE corresponding to the number of frame we have in map (16 * 16) = 256
    SDL_Surface *sElement[MAP_MAX_SIZE] = {NULL};
    // Create array of Element for game
    ELEMENT ST_Elements[MAP_MAX_SIZE] = {0, 0, 0, 0, 0};
    // surface counter to avoid end line case (i have 16 \n more than nS)
    int nS = 0;

    for(int i = 0; i < size; i++){
        switch(pMap->content[i]){
            case E_WALL:
                // set img and blit them
                sElement[nS] = IMG_Load(WALL_PATH);
                SDL_BlitSurface(sElement[nS], NULL, pRootWindow, &positionElement);
                // if in game we set the element structure .
                if(inGame){
                    setElementData(&ST_Elements[nS], E_WALL, 1, nS, &positionElement, WALL_PATH);
                }
                // update postion and nS, only width need to set here eight set in \n case .
                positionElement.x += E_WIDTH;
                nS++;
                break;
                // --
            case E_BOX:
                sElement[nS] = IMG_Load(BOX_PATH);
                SDL_BlitSurface(sElement[nS], NULL, pRootWindow, &positionElement);
                if(inGame) {
                    setElementData(&ST_Elements[nS], E_BOX, 0, nS, &positionElement, BOX_PATH);
                }
                positionElement.x += E_WIDTH;
                nS++;
                break;
                // --
            case E_BOX_OK:
                sElement[nS] = IMG_Load(BOX_OK_PATH);
                SDL_BlitSurface(sElement[nS], NULL, pRootWindow, &positionElement);
                if(inGame){
                    setElementData(&ST_Elements[nS], E_BOX_OK, 1, nS, &positionElement, BOX_OK_PATH);
                }
                positionElement.x += E_WIDTH;
                nS++;
                break;
                // --
            case E_GOAL:
                sElement[nS] = IMG_Load(GOAL_PATH);
                SDL_BlitSurface(sElement[nS], NULL, pRootWindow, &positionElement);
                if(inGame){
                    setElementData(&ST_Elements[nS], E_GOAL, 0, nS, &positionElement, GOAL_PATH);
                }
                positionElement.x += E_WIDTH;
                nS++;
                break;
                // --
            case E_MARIO_TOP:
                sElement[nS] = IMG_Load(MARIO_TOP_PATH);
                SDL_BlitSurface(sElement[nS], NULL, pRootWindow, &positionElement);
                if(inGame){
                    setElementData(&ST_Elements[nS], E_MARIO_TOP, 0, nS, &positionElement, MARIO_TOP_PATH);
                    // set mario position
                    setMarioPosition(&positionMario, sElement[nS]->w, sElement[nS]->h);
                    numSurfaceMario = nS;
                }
                positionElement.x += E_WIDTH;
                nS++;
                break;
            case E_MARIO_BOT:
                sElement[nS] = IMG_Load(MARIO_BOT_PATH);
                SDL_BlitSurface(sElement[nS], NULL, pRootWindow, &positionElement);
                if(inGame){
                    setElementData(&ST_Elements[nS], E_MARIO_BOT, 0, nS, &positionElement, MARIO_BOT_PATH);
                    // set mario position
                    setMarioPosition(&positionMario, sElement[nS]->w, sElement[nS]->h);
                    numSurfaceMario = nS;
                }
                positionElement.x += E_WIDTH;
                nS++;
                break;
                // --
            case E_MARIO_LEFT:
                sElement[nS] = IMG_Load(MARIO_LEFT_PATH);
                SDL_BlitSurface(sElement[nS], NULL, pRootWindow, &positionElement);
                if(inGame){
                    setElementData(&ST_Elements[nS], E_MARIO_LEFT, 0, nS, &positionElement, MARIO_LEFT_PATH);
                    // set mario position
                    setMarioPosition(&positionMario, sElement[nS]->w, sElement[nS]->h);
                    numSurfaceMario = nS;
                }
                positionElement.x += E_WIDTH;
                nS++;
                break;
                // --
            case E_MARIO_RIGHT:
                sElement[nS] = IMG_Load(MARIO_RIGHT_PATH);
                SDL_BlitSurface(sElement[nS], NULL, pRootWindow, &positionElement);
                if(inGame){
                    setElementData(&ST_Elements[nS], E_MARIO_RIGHT, 0, nS, &positionElement, MARIO_RIGHT_PATH);
                    // set mario position
                    setMarioPosition(&positionMario, sElement[nS]->w, sElement[nS]->h);
                    numSurfaceMario = nS;
                }
                positionElement.x += E_WIDTH;
                nS++;
                break;
                // --
            case E_NULL:
                // we need to set a withe bg here
                sElement[nS] = SDL_CreateRGBSurface(SDL_HWSURFACE, E_WIDTH, E_HEIGHT, 32, 0, 0, 0, 0);
                SDL_FillRect(sElement[nS], NULL, SDL_MapRGB(pRootWindow->format, 255, 255, 255));
                SDL_BlitSurface(sElement[nS], NULL, pRootWindow, &positionElement);
                if(inGame){
                    setElementData(&ST_Elements[nS], E_NULL, 0, nS, &positionElement, "null");
                }
                //change the position of element .
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
        // call game function
        gameEventManager(pRootWindow, sElement, ST_Elements, numSurfaceMario);
    } else{
        // call event manager to define the next step in menu functionality
        mapMenuEventManager(pMap, current, pMenuChoice);
        // clean
        cleanWindow(pRootWindow, 0);
    }
    // free surface
    for(int i = 0; i < MAP_MAX_SIZE; i++){
        SDL_FreeSurface(sElement[i]);
    }

}


/**
 * This function set a transition image between map selection and game start .
 * @param pRootWindow SDL_Surface The main window .
 */
void showOverlay(SDL_Surface *pRootWindow, char path[]){
    SDL_Surface *sOverlay = NULL;
    SDL_Rect overlayPosition;

    sOverlay = IMG_Load(path);
    if(sOverlay == NULL){
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    setImageInWindow(pRootWindow, sOverlay, &overlayPosition, 1);
    SDL_Flip(pRootWindow);
    gameStartEvent();
    cleanWindow(pRootWindow, 1);
    SDL_FreeSurface(sOverlay);
}


/**
 * Set a data in surface .
 * @param pRootWindow pRootWindow SDL_Surface An pointer to main window .
 * @param sElem sElem SDL_Surface An array of pointer to the element surface .
 * @param S_eElem ELEMENT The current element in structure element where the position and data is set .
 * @param img int Bool tell if we set an image or just fill rect .
 */
void setValueForSurface(SDL_Surface *pRootWindow, SDL_Surface *sElem, ELEMENT S_eElem, int img){
    SDL_Rect tmpPosition;
    tmpPosition.x = 0;
    tmpPosition.y = 0;
    if(img == 1){
        // load image .
        sElem = IMG_Load(S_eElem.pathImg);
        checkIfSurfaceIsNull(sElem, "Image upload failed .");
        // set postion for sElem[i]
        tmpPosition.x = (u_int16_t) S_eElem.x;
        tmpPosition.y = (u_int16_t) S_eElem.y;
        // and blit
        SDL_BlitSurface(sElem, NULL, pRootWindow, &tmpPosition);
    } else{

        sElem = SDL_CreateRGBSurface(SDL_HWSURFACE, E_WIDTH, E_HEIGHT, 32, 0, 0, 0, 0);
        SDL_FillRect(sElem, NULL, SDL_MapRGBA(pRootWindow->format, 255, 255, 255, 0));
        // set postion for sElem[i]
        tmpPosition.x = (u_int16_t) S_eElem.x;

        tmpPosition.y = (u_int16_t) S_eElem.y;
        // and blit
        SDL_BlitSurface(sElem, NULL, pRootWindow, &tmpPosition);
    }
}


/**
 * Update the root window with the new value make before .
 * @param pRootWindow SDL_Surface An pointer to the main surface .
 * @param sElem SDL_Surface An array of pointer to the element surface .
 * @param S_eElem ELEMENT An pointer to the structure element where the position and data is set .
 * @param nextElem int The position of the next element in an array .
 * @param nextBox  int The position of the next surface after a box if box there .
 */
void updateMainWindow(SDL_Surface *pRootWindow, SDL_Surface *sElem[], ELEMENT *S_eElem, int currentElem, int nextElem){

    // clean main window .
    cleanWindow(pRootWindow, 0);
    // while to create MAP_MAX_SIZE (256) surface and put the correct element in
    for(int i = 0; i < MAP_MAX_SIZE;i++){
        switch(S_eElem[i].id){
            case E_NULL:
                setValueForSurface(pRootWindow, sElem[i], S_eElem[i], 0);
                break;
            case E_BOX:
                if(i != nextElem){
                    setValueForSurface(pRootWindow, sElem[i], S_eElem[i], 1);
                    break;
                }
            case E_WALL:
                setValueForSurface(pRootWindow, sElem[i], S_eElem[i], 1);
                break;
            case E_GOAL:
                setValueForSurface(pRootWindow, sElem[i], S_eElem[i], 1);
                break;
            case E_BOX_OK:
                setValueForSurface(pRootWindow, sElem[i], S_eElem[i], 1);
                break;
            default:
                ;
        } // end switch
    } // end for
    // now we can blit mario and a box if box there .
    if(S_eElem[nextElem].id == E_BOX){
        setValueForSurface(pRootWindow, sElem[nextElem], S_eElem[nextElem], 1);
    }
    // mario
    setValueForSurface(pRootWindow, sElem[currentElem], S_eElem[currentElem], 1);

    SDL_Flip(pRootWindow);

}



//----------------------------------------------------------------------------------------------------------------------