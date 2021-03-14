#include "../headers/binary_functions.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

/* TODO @kswierzy: It is common for write functions that they return the number of bytes
written. */
int writeStructToFile(char* file_name, void* ptr_to_struct, size_t size_of_struct){
    int ret = -1;
    FILE* fp = fopen(file_name, "wb");
    if(fp != NULL){
        fwrite(ptr_to_struct, size_of_struct, 1, fp);
        fclose(fp); 
        ret = 0;
    }
    else
    {
        printf("File: %s not found", file_name);
    }
    return ret;

}

int writeStructToFilePtr(FILE* fp, void* ptr_to_struct, size_t size_of_struct){
    fwrite(ptr_to_struct, size_of_struct, 1, fp);
    return 0;
}


int readStructFromFile(char* file_name, void* ptr_to_struct, size_t size_of_struct){
    int ret = -1;
    FILE* fp = fopen(file_name, "rb");
    if(fp != NULL){
        fread(ptr_to_struct, size_of_struct, 1, fp);
        fclose(fp); 
        ret = 0;
    }
    else
    {
        printf("File: %s not found", file_name);
    }

    return ret;
}

int readStructFromFilePtr(FILE* fp, void* ptr_to_struct, size_t size_of_struct){
    fread(ptr_to_struct, size_of_struct, 1, fp);    
    return 0;
}


