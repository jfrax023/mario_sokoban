/**
 * file_helper.c is a source file where we defined some function to help to access at files located in
 *  a directory .
 * Created by lilith on 11/05/18.
 */
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>

#ifndef WIN32
#include <sys/types.h>
#endif

//----------------------------------------------------------------------------------------------------------------------

struct openDirByPath()

//----------------------------------------------------------------------------------------------------------------------