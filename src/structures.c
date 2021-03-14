#include "../headers/structures.h"
#include "../headers/files_functions.h"
#include "../headers/md5.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>





//////////////////////////////////// VersionBinary functions
/* TODO @kswierzy: pay attention to const correctness. Description and data aren't modified
inside function so they should be declared as const char*. Function user will then now that 
parameters pased through pointer won't be modified inside. */
VersionBinary* createVersionBinary(char *version_description, char *user_data){
    int user_data_size = strlen(user_data);
    VersionBinary *version_binary = (VersionBinary*)calloc(1,sizeof(VersionBinary) + user_data_size);
    version_binary->creation_date = time(NULL);
    version_binary->user_data_size = user_data_size;

    strncpy(version_binary->version_description, version_description, 80);
    getMD5String(user_data,version_binary->version_hash);
    strncpy(version_binary->user_data, user_data, user_data_size);
    
    return version_binary;
}

/* TODO @kswierzy: maybe it would be a better idea to place all display functions in "display" module. */
void displayVersionBinary(VersionBinary* version_binary){
    printf("\n-----------------------------------------------------------");
    printf("\n Description: \n %s \n Date: %s \n",version_binary->version_description , ctime(&(version_binary->creation_date)));
       
}
void displayVersionBinaryWithId(VersionBinary *version_binary, unsigned int id){
    printf("\n-----------------------------------------------------------");
    printf("\n Version id: %d \n Description: \n %s \n Date: %s \n", id, version_binary->version_description , ctime(&(version_binary->creation_date)));
       
}

//////////////////////////////// Version functions
/* TODO @kswierzy: it is not necessary to pass head as double-pointer.
Version is a linked list node so the function could look like this:

Version* getLastVersionNode(Version* head){
    if (head == NULL || (head)->next == NULL)  
        return head;  
  

    Version *last = head;  
  

    while (last->next != NULL)  
    {  
        last = last->next;  
    }  
    return last;
}

Passing head as Version** could be used if your function would return a status code and
head would be used as return argument.
You have already written a function with less error prone interface: getVersionWithId().

Second look:
Address of returned variable is the same as the address of head, so it is not necessary to
return it (double pointers are much more confusing than single pointers).

Let' take a look (by example)

void test(void)
{
    // "version" variable is the beginning of list (allocated on heap) which was read from a file,
    // so "version" value is a heap memory address.
    Version* version = readVersions("path to versions file or directory");

    // you are passing to getLastVersionNode address of "version" variable which resides on stack.
    Version** last = getLastVersionNode(&version)
        {
            // head variable is a pointer to variable "version" stored on stack, so last
            // is the same. What do you think, what would happen if your would write following statemen:
            //    *last = ((*last)->next);
            // You would not only modify variable "last" but also variable "version" stored outside
            // getLastVersionNode function, because last is the address of "version" and with
            // *last your accessing this variable.
            Version **last = head;
            while ((*last)->next != NULL)  
            {
                // What is now the value of last? After this assignment last is not the address of next list record.
                // Last is the address of "next" variable in Version struct.
                last = &((*last)->next);  
            } 
        }

}

 */

Version** getLastVersionNode(Version** head){
    if (*head == NULL || (*head)->next == NULL)  
        return head;  
  

    Version **last = head;  
  

    while ((*last)->next != NULL)  
    {  
        last = &((*last)->next);  
    }  
    return last;
}

/* TODO @kswierzy: maybe findVersionById()? Is it correct to return version with id 5 when
version with id 8 (which not exists) is requested? */
Version* getVersionWithId(Version* head, unsigned int version_id){
    Version* temp = head;
    for(int i = 1; i < version_id; i++){
        if(temp->next == NULL)break;
        temp = temp->next;
    }
    return temp;
}

void addVersionToVersionList(Version **head, Version *version_to_add ){
    Version** last = getLastVersionNode(head);
    if(*last == NULL){
        *last = version_to_add;
    }
    else{
        (*last)->next = version_to_add;
    } /* TODO @kswierzy: removw new line. */

}

int addNewVersionToVersionList(Version **head, Version *version_to_add ){
    int ret = -1;
    
    Version** last = getLastVersionNode(head);
    if(*last == NULL){
        *last = version_to_add;
        ret = 0;
    }
    else{
        if(strcmp((*last)->version_binary->version_hash, version_to_add->version_binary->version_hash) != 0){
            (*last)->next = version_to_add;
            ret = 0;
        }
        else{
            printf("Versions are equal");
            
        }
    }
    return ret; /* TODO @kswierzy: removw new lines. */
    

}

Version* createVersion(VersionBinary* version_binary){
    Version* new_version = calloc(1,sizeof(*new_version));
    new_version->next = NULL;
    new_version->version_binary = version_binary;

    return new_version;

}

/* TODO @kswierzy: it will be much cleaner and more efficient to pass head as Version*.
On most CPU architectures "*head = temp" operation takes one CPU intruction more than "head = temp".
It is so, because (in your case) CPU must first look at address **header and take from it the actual
location of head variable. Otherwise (in the second case) CPU already knows where header variable is
located. */
void freeMemoryFromVersionList(Version** head){
    while((*head) != NULL){
        Version* temp = (*head)->next;
        free((*head)->version_binary);
        free((*head));
        *head = temp;
    }
}


/////////////////////////////////////// Project functions

Project* createProject(char* project_name, char* project_description){
    Project* new_project = calloc(1,sizeof(Project)); /* TODO @kswierzy: what if allocation fails? */
    strncpy(new_project->project_name, project_name, sizeof(new_project->project_name));
    strncpy(new_project->project_description, project_description, sizeof(new_project->project_description));
    strcpy(new_project->project_hash, "");
    new_project->versions_count = 0;
    new_project->latest_update = time(NULL);

    return new_project;
}

void displayProject(Project* project){
    printf("\n \n \n Project: %s \n Description: \n %s \n Version count: %d \n Updated: %s",
         project->project_name, project->project_description, project->versions_count, ctime(&(project->latest_update)));
}


/////////////////////////////////////// Conifig functions

Config* createEmptyConfig(){
    Config* new_config = (Config*)calloc(1,sizeof(Config));
    strcpy(new_config->project_name, "master"); /* TODO @kswierzy: the "magic numbers" comment is also concerns strings. */
    strcpy(new_config->version_description, "empty project");
    return new_config;
}

Config* createConfigFromProject(Project* project){
    Config* new_config = (Config*)calloc(1,sizeof(Config));
    strcpy(new_config->project_name, project->project_name);
    strcpy(new_config->version_description, project->project_description);
    return new_config;
}

void displayConfig(Config* config){
    printf("NOT IMPLEMENTED");
}
