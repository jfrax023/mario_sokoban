/**
 * Windows.h is a header file for windows.c .
 * Created by lilith on 10/05/18.
 * Function List :
 * -- void setNameAndBg(SDL_Surface *sRootWindow);
 * -- void setImageInWindow(SDL_Surface *sRoot, SDL_Surface *sImg, SDL_Rect *positionImg, int center);
 * -- void createMenu(SDL_Surface *sRootWindow, int *pUserMenuChoice, char imgPath[]);
 * -- void cleanWindow(SDL_Surface *sWindow, int color[], int flipFlag);
 * -- void setImgToFrame(SDL_Surface *sElement, SDL_Surface *sRootWindow, SDL_Rect *position);
 * -- void displayMap(Map *pMap, SDL_Surface *pRootWindow, int *current);
*/

#ifndef MARIO_SOKOBAN_WINDOWS_H
#define MARIO_SOKOBAN_WINDOWS_H

#include <SDL/SDL.h>
//----------------------------------------------------------------------------------------------------------------------
/**
 * Set a name and background color .
 * @param sRootWindow SDL_Surface The main window .
 */
void setNameAndBg(SDL_Surface *sRootWindow);

/**
 * Set an image in the main window according to the parameters passed in argument .
 * @param sRoot SDL_Surface The main window where blit image .
 * @param sImg SDL_Surface A surface where the image is .
 * @param positionImg SDL_Rect A sdl sturcture with a postion for image .
 * @param center Bool 0 if no need to be center 1 else .
 */
void setImageInWindow(SDL_Surface *sRoot, SDL_Surface *sImg, SDL_Rect *positionImg, int center);

/**
 * Blit an image already put in sElement to the main window .
 * @param sElement SDL_Surface The current surface where we work .
 * @param sRootWindow SDL_Surface The main window .
 * @param position SDL_Rect The position of this surface .
 */
void setImgToFrame(SDL_Surface *sElement, SDL_Surface *sRootWindow, SDL_Rect *position);

/**
 * Create a séléction menu corresponding to one surface where we put a menu image and "blitt" them
 *  in the main window .After that she call the event function who will wait to get an user choice .
 * @param sRootWindow SDL_Surface The main window .
 * @param pUserMenuChoice int One pointer on userMenuChoice variable located in main function .
 * @param imgPath char The path to access to image .
 */
void createMenu(SDL_Surface *sRootWindow, int *pUserMenuChoice, char imgPath[]);

/**
 * This function clean the current main window in him re color and flip them .
 * @param sWindow SDL_Surface The main window .
 * @param color int Array with rgb color [r, g, b] nedded .
 * @param flipFlag int A flag corresponding to tell if we need to SDL_Flip this surface or not, 0 dont flip 1 flip .
 */
void cleanWindow(SDL_Surface *sWindow, int color[], int flipFlag);

/**
 * This function receive a map in parameter and translate them to an SDL window .
 * @param pMap Map An pointer to the map structure where is stored the map data .
 * @param pRootWindow SDL_Surface An pointer to main window .
 * @param current int An pointer to the variable current to manage while .
 * @param pMenuChoice int An pointer to the array menuChoice .
 */
void displayMap(Map *pMap, SDL_Surface *pRootWindow, int *current, int *pMenuChoice);


void tmpShowEdition(SDL_Surface *sRootWindow, int *pUserChoice, char imgPath[]);

//----------------------------------------------------------------------------------------------------------------------
#endif //MARIO_SOKOBAN_WINDOWS_H
