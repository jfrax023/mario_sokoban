/**
 * error_helper.c is a source file withe some function to set a error in code like a control of pointer is null make this etc
 * Created by lilith on 10/05/18.
 */
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

//----------------------------------------------------------------------------------------------------------------------
/**
 * Check if the sruface is null and raise an error and exit program
 * @param toCheck The surface will checking
 * @param message An message to help for debug
 */
void checkIfSurfaceIsNull(SDL_Surface *toCheck, char message[]){
    if(toCheck == NULL){
        fprintf(stderr, "%s => %s\n", message, SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

//----------------------------------------------------------------------------------------------------------------------
