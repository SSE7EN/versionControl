#include "../headers/binary_functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int getFileSize(char *file_name){ 
    // opening the file in read mode 
    FILE* fp = fopen(file_name, "rb"); 
  
    // checking if the file exist or not 
    if (fp == NULL) { 
        printf("File Not Found!\n"); 
        return -1; 
    } 
  
    fseek(fp, 0, SEEK_END); 
  
    // calculating the size of the file 
    int res = ftell(fp); 
  
    // closing the file 
    fclose(fp); 
  
    return res; 
}
int getFileSizeWFilePtr(FILE *fp){
  
  
    fseek(fp, 0, SEEK_END); 
  
    // calculating the size of the file 
    int res = ftell(fp); 
  
    fseek(fp, 0, SEEK_SET);
  
    return res; 
}

char* readFileAsBinary(char *file_name){
    // opening the file in read mode 
    FILE* fp = fopen(file_name, "rb"); 
  
    // checking if the file exist or not 
    if (fp == NULL) { 
        printf("File Not Found!\n"); 
        return NULL; 
    }
    
    //alocate mem to read data
    int size = getFileSizeWFilePtr(fp);
    char* res = (char*)malloc(size+1);
    
    //read data
    fread(res, sizeof(char), size,fp);
    res[size] = '\0';
    fclose(fp);
    
    return res;

}


int createFile(char* file_name){
    int ret = -1;

    //check if file exist
    if( access( file_name, 0) != -1 ) {
        printf("Project: %s already exist", file_name);
    } else {
        FILE* fp = fopen(file_name, "wb");
        if(fp != NULL){
            fclose(fp);
            ret = 0; 
        }
        else printf("Something went wrong");
    }
    return ret;
}
