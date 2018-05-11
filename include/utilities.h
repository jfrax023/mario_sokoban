/**
 * utilities.h is a header where we defined some #define and structure for this programme .
 * Created by lilith on 10/05/18.
 * --- Define ---
 * - ROOT_WINDOW_*ARG*  : Define for a main window like height and width .
 * - *ELEMENT*_PATH     : Define path for an img called élément of the game like caisse.jpg coresponding to the box etc.
 * - LEVEL_*MODE*_DIR   : Define path to access at levels organised by difficulty .
 */

#ifndef MARIO_SOKOBAN_UTILITIES_H
#define MARIO_SOKOBAN_UTILITIES_H

// Data for main window called sRootWindow in main
#define ROOT_WINDOW_WIDTH 896
#define ROOT_WINDOW_HEIGHT 896
#define ROOT_WINDOW_NB_PIXEL (ROOT_WINDOW_WIDTH * ROOT_WINDOW_HEIGHT)
#define ROOT_WINDOW_NAME "mario_sockoban"

// path images
#define BOX_PATH "img/caisse.jpg"
#define BOX_OK_PATH "img/caisse_ok.jpg"
#define MARIO_BOT_PATH "img/mario_bas.gif"
#define MARIO_RIGHT_PATH "img/mario_droite.gif"
#define MARIO_LEFT_PATH "img/mario_gauche.gif"
#define MARIO_TOP_PATH "img/mario_haut.gif"
#define MENU_PATH "img/menu.jpg"
#define LVL_MENU_PATH "img/level_menu.png"
#define WALL_PATH "img/mur.jpg"
#define GOAL_PATH "img/objectif.png"

// levels directory
#define LEVEL_EASY_DIR "levels/easy/"
#define LEVEL_MEDIUM_DIR "levels/medium/"
#define LEVEL_HARD_DIR = "levels/hard/"


#endif //MARIO_SOKOBAN_UTILITIES_H
