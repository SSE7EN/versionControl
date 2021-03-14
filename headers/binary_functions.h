#ifndef BINARY_FUNCTIONS_H
#define BINARY_FUNCTIONS_H

#include "structures.h"

/**
 * @brief function returns user data as binary from File
 */
char* readUserDataAsBinaryFromFile(char* filename /**< filename from which you read user_data */);

/**
 * @brief function write version_binary to File
 */
void writeVersionBinaryFromToVersionsFile(VersionBinary *version_binary /**<version binary to write*/ , char* filename/**< filename to which you write*/);


/**
 * @brief write struct to file
 */
int writeStructToFile(char* file_name, void* ptr_to_struct, size_t size_of_struct);

/**
 * @brief read struct from file
 */
int readStructFromFile(char* file_name, void* ptr_to_struct, size_t size_of_struct);

/**
 * @brief write struct to file pointer
 */
int writeStructToFilePtr(FILE* fp, void* ptr_to_struct, size_t size_of_struct);

/**
 * @brief read struct from file pointer
 */
int readStructFromFilePtr(FILE* fp, void* ptr_to_struct, size_t size_of_struct);





#endif