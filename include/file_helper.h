/**
 * file_helper.h is a header for file_helper.c .
 * Created by lilith on 13/05/18.
 * Function Lists :
 * -- int getNbFileInDir(char dirPath[], char fExt[]);  Count nb file in dir .
 * -- void initMap(FileName *map, int nbInit); Initialize a Map structure
 * -- void setNameInMap(char dirPath[], char fExt[] ,FileName *map); Set correct value in Map structure .
 * -- void setContentByFileName(char dirPath[], Map *map); Open a file and extract the content and put them in Map structure .
 */

#ifndef MARIO_SOKOBAN_FILE_HELPER_H
#define MARIO_SOKOBAN_FILE_HELPER_H

#include "utilities.h"

//----------------------------------------------------------------------------------------------------------------------

/**
 * Count the number of file found in a directory passed in parameter .
 * @param dirPath char A path where search .
 * @param fExt char An flag who tell the extention we looking for . 0 for all file
 * @return int nbFile The number of file found .
 */
int getNbFileInDir(char dirPath[], char fExt[]);


/**
 * TO REMOVE OR REWIND
 * Initialize the filname structure to 0 ;
 * @param map Map An pointer on the Map structure .
 * @param nbInit Int The number of structure who need to initialize defined by the number of file found
 *                    by getNbFileInDir
 */
void initMap(Map *map, int nbInit, int fLvl);


/**
 * Set the Map structure value by the name we found in a directory passed in the paramèter .The number corresponding to
 *  the number where the filename is located like first file = first 'map' . The name is a filename .
 * @param dirPath char The path where get filename
 * @param fExt char The extention of file in this directory . 0 = get all file .
 * @param map Map An pointer to the structure Map designed to this function .
 */
void setNameInMap(char dirPath[], char fExt[] ,Map *map);


/**
 * Open a file with a filename and get the content to put them in a array defined for in the Map structure .The content
 *  is returned an integer and we convert him to get a letter .
 * @param dirPath char The directory path .
 * @param map Map The map structure .
 */
void setContentByFileName(char dirPath[], Map *map);


//----------------------------------------------------------------------------------------------------------------------
#endif //MARIO_SOKOBAN_FILE_HELPER_H
