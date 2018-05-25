/**
 * utilities.h is a header where we defined some #define and structure for this programme .
 * Created by lilith on 10/05/18.
 * --- Define ---
 * - ROOT_WINDOW_*ARG*   : Define for a main window like height and width .
 * - *ELEMENT*_PATH      : Define path for an img called élément of the game like caisse.jpg coresponding to the box etc.
 * - LEVEL_*MODE*_DIR    : Define path to access at levels organised by difficulty .
 *                          we can just made 12*12 to know how much frame this mode have .
 * - A_*SIZE*            : Define some sizes for array definition .
 * - MAP_MAX_SIZE        : Define a max size for stored the file content representing a map .
 *
 * Structures :
 * - typedef enum Difficulty Difficulty; One enumeration where we define the difficulties possible .
 * - typedef struct Map Map; The 'map' structure to store datas for 'map' entity .
 *
 * Function lists :
 * - void setDifficulty(int userChoice, Difficulty LvlMode); Set a Difficulty structure according to userChoice .
 * - void showMenuAndSelectMap(SDL_Surface *sRootWindow, Map *MapToPlay); The menu fonctionnalities .
 * - void getMapData(SDL_Surface *pRootWindow, Map *pMapToPlay, int *pMenuChoice, char levelPath[], int fLvl); Fonction for the third menu .
 * - void setPreviousAndNext(Map *map,int  nbFile); Set the previous an next variable in Map structure .
 * - void createMapMenu(SDL_Surface *sRootWindow, Map *MapToPlay, Map *PS_tmpMap, int *menuChoice, int nbFile);
 * - void initMapStructForEdit(Map *editMap, int difficulty);
 * - char getPathImage(int numImage, char pathImg[]);
 * - void initMapStructForEdit(Map *pEditMap, int difficulty);
 * - int checkIfMarioIsIn(ELEMENT *S_elem, int cursor);
 * - int checkIfObjIsHere(ELEMENT *S_elem, int nbObjectif);
 * - int checkIfBoxIsHere(ELEMENT *S_elem, int nbObjectif);
 * - void checkElementInEditMap(ELEMENT *S_elem, int nbObj, int *numImage, int cursor);
 * -
 */

#ifndef MARIO_SOKOBAN_UTILITIES_H
#define MARIO_SOKOBAN_UTILITIES_H
//----------------------------------------------------------------------------------------------------------------------
// Include
#include <SDL/SDL.h>
// Data for main window called sRootWindow in main
#define ROOT_WINDOW_WIDTH (16 * 34)
#define ROOT_WINDOW_HEIGHT (16 * 34)
#define ROOT_WINDOW_NB_PIXEL (ROOT_WINDOW_WIDTH * ROOT_WINDOW_HEIGHT)
#define ROOT_WINDOW_NAME "mario_sockoban"

// element size
#define E_WIDTH 34
#define E_HEIGHT 34

// array size, is a base size often used like 50, 100, 500, 1000
#define A_HALF_FIFTY 25
#define A_HALF_HUNDR 50
#define A_HUND 100
#define A_HALF_THOUS 500
#define A_THOUS 1000
// for map content max is 16*16  256
#define MAP_MAX_SIZE (16*16)
#define NB_FRAME_IN_LINE 16
#define NB_LINE 16

// path images
#define BOX_PATH "img/caisse.jpg"
#define BOX_OK_PATH "img/caisse_ok.jpg"
#define MARIO_BOT_PATH "img/mario_bas.gif"
#define MARIO_RIGHT_PATH "img/mario_droite.gif"
#define MARIO_LEFT_PATH "img/mario_gauche.gif"
#define MARIO_TOP_PATH "img/mario_haut.gif"
#define MENU_PATH "img/menu.jpg"
#define LVL_MENU_PATH "img/level_menu.png"
#define EDITION_MENU_PATH "img/edition.png"
#define WALL_PATH "img/mur.jpg"
#define GOAL_PATH "img/objectif.png"
#define OVERLAY_PATH "img/overlay.png"
#define END_GAME_PATH "img/end_game.png"


// define letter for elements
#define E_WALL 'O'
#define E_BOX 'A'
#define E_BOX_OK 'C'
#define E_MARIO_TOP 'T'
#define E_MARIO_RIGHT 'R'
#define E_MARIO_LEFT 'L'
#define E_MARIO_BOT 'B'
#define E_GOAL 'X'
#define E_NULL ' '
#define E_END_LINE '\n'

// levels directory
#define LEVEL_EASY_DIR "levels/easy/"
#define LEVEL_MEDIUM_DIR "levels/medium/"
#define LEVEL_HARD_DIR "levels/hard/"

// file extention
#define E_TEXT ".txt"

// objectif by difficulty
#define OBJ_EASY 3
#define OBJ_MEDIUM 4
#define OBJ_HARD 5
// Structure definition
/**
 * Just a simple enumeration where we list the difficulty possible .
 */
typedef enum Difficulty Difficulty;
enum Difficulty{
    EASY, MEDIUM, HARD
};


/**
 * Structure Map, this type is designed to contains a data in relation with a map strored in a file .
 *@var Int number Is number or the position of map .
 *@var char name Is name of this map corresponding to the filname in directory .
 *@var int difficulty One number corresponding to the level of difficulty séléctionned by the user (0, 1, 2) .
 *@var char content The content of file corresponding to the representation of map in a file .
 */
typedef struct Map Map;
struct Map{
    int number;
    int previous;
    int next;
    int difficulty;
    char name[A_HALF_HUNDR];
    char content[A_HALF_THOUS];
};

/**
 * Structure Element corresponding to an élément of game like caisse or wall etc ... Here we stored some data to help us
 *  to manage movement .
 *  @var char id A letter representing this élément in file .
 *  @var int block Bool said if this élément is fix and he block any movement .
 *  @var int limitX A number corresponding to the end pixel of this élément (surface->x + E_WIDTH)
 *  @var int limitY A number corresponding to the end pixel of this élément (surface->y + E_EIGHT)
 *  @var int numSurface An id to help us to access at the surface corresponding to this élément .
 */
typedef struct ELEMENT ELEMENT;
struct ELEMENT{
    char id;
    int block;
    int numSurface;
    int x;
    int y;
    int limitX;
    int limitY;
    char pathImg[A_HALF_HUNDR];
};
void copyMap(Map *MapToPlay, Map copy);


/**
 * This function set the difficulty mode the user have choose and define the path to access to the directory where
 *  maps as stored .
 * @param userChoice int The number corresponding to the difficulty associated in menu .
 * @param LvlMode Difficulty An enumeration representing the current difficulty .
 * @param lvlPath char The path where we can found the 'map' representation in a file .
 */
void setDifficulty(int userChoice, Difficulty *LvlMode, char lvlPath[]);

/**
 * This function return the path for an image based on the num received .
 * @param numImage An number corresponding to the image selected .
 * @param pathImg A string where store the path .
 * @return char A letter representing the image in map .
 */
char getPathImage(int numImage, char pathImg[]);

/**
 * This function display allow to navigate in the differents menu of selection .We have 3 menu :
 *  - menu 1 : He'll allow to choose between a playable mode or to map editon .
 *  - menu 2 : Allow to choose the difficulty for the game .Easy, medium, hard .More higher is a choice more difficult the
 *              map is
 *  - menu 3 : Display a map and allow to navigate to the next or the previous map if possible, and select them .
 *  also allows you to move between the menus with specific key (F9 = first menu, F8 = second menu) .
 * @param sRootWindow SDL_Surface The main window where display menu
 * @param MapToPlay Map One pointer to the Map structure we will store the map chosen by user .
 */
void showMenuAndSelectMap(SDL_Surface *sRootWindow, Map *MapToPlay);

/**
 * Initialize the Map structure with a first value .
 * @param editMap Map An pointer to currentMap variable .
 * @param difficulty A number corresponding to the difficulté chosen .
 */
void initMapStructForEdit(Map *pEditMap, int difficulty);

/**
 * This function define an array of Map structure to store the data corresponding to an map located in a file .After
 *  she create this array she call  functions to set a différents variable in like a name and content .After that we
 *  can call the function to display a third menu with the data we have stored in this array .
 * @param pRootWindow SDL_Surface An pointer to main window .
 * @param pMapToPlay Map An pointer to the Map structure where we will storing the map the user have chose .
 * @param pMenuChoice int An pointer to the array where we store the choice made by user .
 * @param levelPath char The path where search map
 * @param fLvl int The difficulty chosen by user .
 */
void getMapData(SDL_Surface *pRootWindow, Map *pMapToPlay, int *pMenuChoice, char levelPath[], int fLvl);

/**
 * This function set value to previous an next variable to the map structure .
 * @param map Map An pointer to the first structure Map .
 * @param nbFile int The number of file found in directory .
 */
void setPreviousAndNext(Map *map,int  nbFile);


/**
 * This function define an array of Map structure to store the data corresponding to an map located in a file .After
 *  she create this array she call  functions to set a différents variable in like a name and content .After that we
 *  can call the function to display a third menu with the data we have stored in this array .
 * @param pRootWindow SDL_Surface An pointer to main window .
 * @param pMapToPlay Map An pointer to the Map structure where we will storing the map the user have chose .
 * @param pMenuChoice int An pointer to the array where we store the choice made by user .
 * @param levelPath char The path where search map
 * @param fLvl int The difficulty chosen by user .
 */
void createMapMenu(SDL_Surface *sRootWindow, Map *MapToPlay, Map *PS_tmpMap, int *menuChoice, int nbFile);

/**
 * check if mario is already in map and cannot be displayed another time .
 * @param S_elem ELEMENT An pointer to the array of element structure .
 * @param int The current position represented by cursor variable .
 * @return 1 if mario is already here 0 else .
 */
int checkIfMarioIsIn(ELEMENT *S_elem, int cursor);


/**
 * check if objectives and box is already in map and cannot be displayed another time .
 * @param S_elem ELEMENT An pointer to the array of element structure .
 * @return 1 if mario is already here 0 else .
 */
int checkIfObjIsHere(ELEMENT *S_elem, int nbObjectif);

/**
 * check if objectives and box is already in map and cannot be displayed another time .
 * @param S_elem ELEMENT An pointer to the array of element structure .
 * @param nbObjectif int The number of objectives the map have depending a difficulty selected .
 * @return 1 if mario is already here 0 else .
 */
int checkIfBoxIsHere(ELEMENT *S_elem, int nbObjectif);

/**
 * Check and update the image is possible to diplay in relation with the presence of elements or not .
 * @param S_elem ELEMENT An pointer to the array of structure element .
 * @param nbObj int A number of objectives the mode have .
 * @param numImage An pointer to the variable numImage .
 * @param int The current element represented by cursor variable .
 */
void checkElementInEditMap(ELEMENT *S_elem, int nbObj, int *numImage, int cursor);



//----------------------------------------------------------------------------------------------------------------------
#endif //MARIO_SOKOBAN_UTILITIES_H
