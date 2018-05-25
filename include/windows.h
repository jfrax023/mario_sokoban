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
 * -- void showOverlay(SDL_Surface *pRootWindow);
 * -- void updateMainWindow(SDL_Surface *pRootWindow, SDL_Surface *sElem[], ELEMENT *S_eElem,
 *                    int nextElem, int nextBox);
 * -- void setValueForSurface(SDL_Surface *pRootWindow, SDL_Surface *sElem, ELEMENT S_eElem, int img);
 * -- int displayMenuDifficulty(SDL_Surface *pRootWindow);
 * -- void diplayMapToEdit(SDL_Surface *pRootWindow, SDL_Surface *psElem, int cursor);
 * -- void showChangeInMapEdit(SDL_Surface *pRootWindow, SDL_Surface *psElem, ELEMENT *PS_Elem);
 * -- void setValueForMapToEdit(SDL_Surface *pRootWindow, SDL_Surface *psElem, ELEMENT *PS_Elem,
 *                        int currentFlag, int cursor);
 * -- void setValueForSurface(SDL_Surface *pRootWindow, SDL_Surface *sElem, ELEMENT S_eElem, int img);
 * --
*/

#ifndef MARIO_SOKOBAN_WINDOWS_H
#define MARIO_SOKOBAN_WINDOWS_H

#include <SDL/SDL.h>
#include "utilities.h"
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
 * Create a séléction menu corresponding to one surface where we put a menu image and "blitt" them
 *  in the main window .After that she call the event function who will wait to get an user choice .
 * @param sRootWindow SDL_Surface The main window .
 * @param pUserMenuChoice int One pointer on userMenuChoice variable located in main function .
 * @param imgPath char The path to access to image .
 */
void createMenu(SDL_Surface *sRootWindow, int *pUserMenuChoice, char imgPath[]);

/**
 * This function update the current map with a new image of an element chosen by user .
 * @param pRootWindow SDL_Surface The main window .
 * @param psElem SDL_Surface An pointer to the surface array corresponding to the elements of the game .
 * @param PS_Elem ELEMENT An pointer to the array of structure element .
 * @param currentFlag int the current surface to update .
 * @param cursor An pointer to the variable cursor to representing the current elements where we work .
 * @param img A number who tell what the image we need to display .
 */
void showChangeInMapEdit(SDL_Surface *pRootWindow, SDL_Surface *psElem, ELEMENT *PS_Elem);

/**
 * This function clean the current main window in him re color and flip them .
 * @param sWindow SDL_Surface The main window .
 * @param flipFlag int A flag corresponding to tell if we need to SDL_Flip this surface or not, 0 dont flip 1 flip .
 */
void cleanWindow(SDL_Surface *sWindow, int flipFlag);


/**
 * This function receive a map in parameter and translate them to an SDL window .
 * @param pMap Map An pointer to the map structure where is stored the map data .
 * @param pRootWindow SDL_Surface An pointer to main window .
 * @param current int An pointer to the variable current to manage while .
 * @param pMenuChoice int An pointer to the array menuChoice .
 * @param inGame in Bool 0 tell not in game 1 game is started .
 */
void displayMap(Map *pMap, SDL_Surface *pRootWindow, int *current, int *pMenuChoice, int inGame);

/**
 * This function set a transition image between map selection and game start .
 * @param pRootWindow SDL_Surface The main window .
 */
void showOverlay(SDL_Surface *pRootWindow, char path[]);

/**
 * This function display the map who will be editing by the user .Actually is just a white surface end one green surface
 *  representing the cursor where we work .
 * @param pRootWindow SDL_Surface The main window .
 * @param psElem SDL_Surface An pointer to the surface array corresponding to the elements of the game .
 * @param cursor int An pointer to the variable cursor to representing the current elements where we work .
 * @param SDL_Rect An pointer to the variable posSurface for position of this surface .
 */
void setValueForMapToEdit(SDL_Surface *pRootWindow, SDL_Surface *psElem, ELEMENT *PS_Elem,
                          int currentFlag, int cursor, SDL_Rect *positionSurface);

/**
 * Set a data in surface .
 * @param pRootWindow pRootWindow SDL_Surface An pointer to main window .
 * @param sElem SDL_Surface An array of pointer to the element surface .
 * @param S_eElem ELEMENT The current element in structure element where the position and data is set .
 * @param img int Bool tell if we set an image or just fill rect .
 */
void setValueForSurface(SDL_Surface *pRootWindow, SDL_Surface *sElem, ELEMENT S_eElem, int img);

/**
 * Update the root window with the new value make before .
 * @param pRootWindow SDL_Surface An pointer to the main surface .
 * @param sElem SDL_Surface An array of pointer to the element surface .
 * @param S_eElem ELEMENT An pointer to the structure element where the position and data is set .
 * @param nextElem int The position of the next element in an array .
 * @param nextBox  int The position of the next surface after a box if box there .
 */
void updateMainWindow(SDL_Surface *pRootWindow, SDL_Surface *sElem[], ELEMENT *S_eElem, int currentElem, int nextElem);



//----------------------------------------------------------------------------------------------------------------------
#endif //MARIO_SOKOBAN_WINDOWS_H
