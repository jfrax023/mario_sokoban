/**
 * file_helper.c is a source file where we defined functions to help to access and read a files located in
 *  a directory .
 * Created by lilith on 11/05/18.
 */
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include "utilities.h"
#include <string.h>

#ifndef WIN32
#include <sys/types.h>
#endif

//----------------------------------------------------------------------------------------------------------------------

/**
 * Count the number of file found in a directory passed in parameter .
 * @param dirPath char A path where search .
 * @param fExt char An flag who tell the extention we looking for . 0 for all file
 * @return int nbFile The number of file found .
 */
int getNbFileInDir(char dirPath[], char fExt[]){
    int nbFile = 0;
    DIR *rep = NULL;
    struct dirent *fileRead = NULL;
    rep = opendir(dirPath);
    if(rep == NULL){
        perror("");
        exit(EXIT_FAILURE);
    }
    // dir open
    if(fExt == 0){
        while((fileRead = readdir(rep)) != NULL){
            // exculde the hide file
            if(strcmp(fileRead->d_name, ".") != 0 && strcmp(fileRead->d_name, "..") != 0){
                nbFile++;
            }
        }
    } else{
        while((fileRead = readdir(rep)) != NULL){
            if(strstr(fileRead->d_name, fExt) != NULL){
                nbFile++;
            }
        }
    }
    // close dir
    closedir(rep);
    // return the number of file found .
    return nbFile;

}


/**
 * Set the Map structure value by the name we found in a directory passed in the paramèter .The number corresponding to
 *  the number where the filename is located like first file = first 'map' . The name is a filename .
 * @param dirPath char The path where get filename
 * @param fExt char The extention of file in this directory . 0 = get all file .
 * @param map Map An pointer to the structure Map designed to this function .
 */
void setNameInMap(char dirPath[], char fExt[] ,Map *map){
    DIR *rep = NULL;
    int i = 0;
    struct dirent *fileRead = NULL;
    rep = opendir(dirPath);
    if(rep == NULL){
        perror("");
        exit(EXIT_FAILURE);
    }
    // dir open
    if(fExt == 0){
        while((fileRead = readdir(rep)) != NULL){
            if(strcmp(fileRead->d_name, ".") != 0 && strcmp(fileRead->d_name, "..") != 0){
                map[i].number = i + 1;
                strcpy(map[i].name, fileRead->d_name);
                i++;
            }
        }
    } else{
        while((fileRead = readdir(rep)) != NULL){
            if(strstr(fileRead->d_name, fExt) != NULL){
                map[i].number = i + 1;
                strcpy(map[i].name, fileRead->d_name);
                i++;
            }
        }
    }
    // close dir
    closedir(rep);
}

/**
 * Open a file with a filename and get the content to put them in a array defined for in the Map structure .The content
 *  is returned an integer and we convert him to get a letter .
 * @param dirPath char The directory path .
 * @param map Map The map structure .
 */
void setContentByFileName(char dirPath[], Map *map){
    FILE *file = NULL;
    int current = 0;
    char tmp[2] = "";
    char path[100] = "";
    strcpy(path, dirPath);
    strcat(path, map->name);
    file = fopen(path, "r");
    if(file != NULL){
        // while to EOF
        do{
            current = fgetc(file);
            if(current != EOF){
                // fgetc retrun an integer we use a tmp var to convert on letter and put them after the last caractère .
                sprintf(tmp, "%c", current);
                strcat(map->content, tmp);
                tmp[0] = 0;
                tmp[1] = 0;
            } else{
                strcat(map->content, "\0");
            }
        }while(current != EOF);

        fclose(file);
    }
}

/**
 * Save the map created by user in the directory in a file called by the filname send in parameter .
 * @param directory char The path where store the new map according to the difficulty chosen .
 * @param fileName char The name to save file .
 * @param S_elem ELEMENT An pointer to the array of structure element .
 * @param openMode  char A letter corresponding to the mode to open file .
 */
void saveMapInDir(char directory[], char fileName[], ELEMENT *S_elem, char openMode[]){
    char path[200] = "";
    strcpy(path, directory);
    strcat(path, fileName);
    FILE *file = NULL;
    file = fopen(path, openMode);
    if(file != NULL){
        // open
        for(int i = 0; i < MAP_MAX_SIZE; i++){
            if(i % 16 == 0 && i != 0){
                fputc('\n', file);
                continue;
            }
            fputc(S_elem[i].id, file);

        }
    } else{
        fprintf(stderr, "Fatal Error on File in saveMapInDir");
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    // close
    fclose(file);
}

/**
 * Check if the name passed in parameter is the same to one another in a directory passed in parameter .
 * @param directory char The path where we need to search .
 * @param fileName char The name to search .
 * @return int bool 1 if the name is already present 0 else .
 */
int checkFileNameInDir(char directory[], char fileName[]){
    int same = 0;
    DIR *rep = NULL;
    struct dirent *fileRead = NULL;
    rep = opendir(directory);
    if(rep == NULL){
        perror("");
        exit(EXIT_FAILURE);
    }
    while((fileRead = readdir(rep)) != NULL){
        // exculde the hide file
        if(strcmp(fileRead->d_name, ".") != 0 && strcmp(fileRead->d_name, "..") != 0){
            if(strcmp(fileRead->d_name, fileName) == 0){
                same++;
            }
        }
    }
    // close dir
    closedir(rep);
    // return the number of file found .
    return same;
}


//----------------------------------------------------------------------------------------------------------------------