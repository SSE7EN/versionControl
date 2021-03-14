#ifndef FILE_FUNCTIONS_H
#define FILE_FUNCTIONS_H

/* TODO @kswierzy: there is no need to include stdlib,h in header. It is better to place
it in source (.c) to reduce public dependency of this module. This is important in large
projects where included files can change. Every change in "foo.h" which is used internally
in bar.c file (but included in bar.h) would cause to the need of recompilation all files
(modules) which include bar.h. */
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief function returns File length
 */
/* TODO @kswierzy: const char*. */
int getFileSize(char *file_name);

/**
 * @brief function returns File length
 */
int getFileSizeWFilePtr(FILE *fp);

/**
 * @brief function returns the line count of file
 */
int getFileLineCount(char *file_name);

/**
 * @brief function returns the file data
 */
char* readFileAsBinary(char *file_name);


/**
 * @brief createsFile
 * 
 *  returns 0 if ok -1 if something went wrong
 */
int createFile(char* file_name); 



#endif