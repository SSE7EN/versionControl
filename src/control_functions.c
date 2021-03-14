#include "../headers/control_functions.h"
#include "../headers/binary_functions.h"
#include "../headers/structures.h"
#include "../headers/utility_functions.h"
#include "../headers/files_functions.h"

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <dirent.h>


Config* loadConfig(){
    Config* config = calloc(1,sizeof(Config));
    readStructFromFile("./.vc/config", config, sizeof(Config));

    return config;
}


int vcCreateProjectForInit(Project* proj){
    int ret = -1;
    char* project_file_name = concat( "./.vc/projects/",proj->project_name);
    int check = createFile(project_file_name);
    if(check == 0){
        int check = writeStructToFile(project_file_name, proj, sizeof(*proj));
        if(check == 0){
            printf("Project: %s was successfull created", proj->project_name);
            ret = 0;
        }
    }

    free(project_file_name);

    return ret;
}



int vcInitConfigFile(){
    int check = -1;
    Project* master_project = createProject("master", "Master project");

    check = vcCreateProjectForInit(master_project);
    if(check == 0){
        Config* new_config = createConfigFromProject(master_project);
        writeStructToFile("./.vc/config", new_config, sizeof(Config));
        free(new_config);
    }
    else printf("Something went wrong :/");
    
    free(master_project);

    return check;
}

void vcInit(){
    struct stat st = {0};
    // check if dir exist
    if (stat("./.vc", &st) == -1) {
        mkdir("./.vc", 0700);
        mkdir("./.vc/projects", 0700);
        int check = vcInitConfigFile();
        if(check == 0)  printf("\n Version control initialized: Success");


    }

    else printf("\n Already initialized");
}

int checkIfInit(){
    struct stat st = {0};
    int ret = -1;
    // check if ./.vc exist
    if (stat("./.vc", &st) == 0){
        ret = 0;
    }
    return ret;
}

void vcCreateProject(char* project_name, char* project_description){
    Project* new_project = createProject(project_name, project_description);
    char* project_file_name = concat( "./.vc/projects/",project_name);

    int check = createFile(project_file_name);
    if(check == 0){
        int check = writeStructToFile(project_file_name, new_project, sizeof(*new_project));
        if(check == 0) printf("\n Project: %s was successfull created", new_project->project_name);
    }

    free(project_file_name);
    free(new_project);
}


void vcProjectInfo(Project* proj){
    displayProject(proj);
    
}

void vcGetProjects(){
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("./.vc/projects/")) != NULL) {
    Project* project = calloc(1,sizeof(Project));
    /* print all the files and directories within directory */
    while ((ent = readdir (dir)) != NULL) {
        if(ent->d_name[0] == '.') continue;
        char* project_file_name = concat( "./.vc/projects/", ent->d_name);
        int check = readStructFromFile(project_file_name, project, sizeof(*project));
        if(check == 0) displayProject(project);
        free(project_file_name);
    }
    free(project);
    closedir (dir);
    } else {
        /* could not open directory */
        printf("Something went wrong");
        perror ("");
    }
}

void vcGetVersions(Version* head){
    int id = 1;
    printf("\n \n");
    while(head != NULL){
        displayVersionBinaryWithId(head->version_binary,id);
        head = head->next;
        id++;
        
    }
}

void vcCheckout(char* project_name){
    char* project_file_name = concat( "./.vc/projects/", project_name);
    Project* proj = calloc(1,sizeof(Project));
    int check = readStructFromFile(project_file_name, proj, sizeof(*proj));
    if(check == 0){
        Config* new_config = createConfigFromProject(proj);
        check = writeStructToFile("./.vc/config", new_config, sizeof(*new_config));
        if(check == 0){
            printf("\n Project: %s", proj->project_name);
        }

        free(new_config);
    }
    free(proj);    
    free(project_file_name);   
}



void loadProjectWithVersions(Config* config, Project** project, Version** version_head){
    char* project_file_name = concat( "./.vc/projects/", config->project_name);
    
    *project = (Project*)calloc(1,sizeof(**project));
    FILE* fp = fopen(project_file_name, "rb");
    fread(*project, sizeof(**project), 1, fp);

    VersionBinary tempVersion;
    int size;
    for(int i =1; i <= (*project)->versions_count; i++){
        fread(&tempVersion, sizeof(tempVersion), 1, fp);
        size = tempVersion.user_data_size;

        VersionBinary* version_binary = calloc(1,sizeof(*version_binary) + size);
        *version_binary = tempVersion;
        fread(version_binary->user_data, sizeof(char), version_binary->user_data_size, fp);
        
        Version* new_versoin_node = createVersion(version_binary);
        addVersionToVersionList(version_head, new_versoin_node);
    }
    fclose(fp);
    free(project_file_name);

}

void saveProjectWithVersions(Project* project, Version* head){
    char* project_file_name = concat( "./.vc/projects/", project->project_name);
    
    FILE* fp = fopen(project_file_name, "wb");
    if(fp != NULL){
        fwrite(project, sizeof(*project), 1, fp);
        while(head != NULL){
            VersionBinary* binary = head->version_binary;
            fwrite(binary, sizeof(*binary), 1, fp);
            fwrite(binary->user_data, sizeof(char), binary->user_data_size,fp);
            head = head->next;
        }
        fclose(fp);
    }
    else{
        printf("Error while opening: %s", project_file_name);
    }

    free(project_file_name);
}

void vcPush(char* push_file, char* version_description, Project* project, Version** head){
    char* user_data = readFileAsBinary(push_file);
    if(user_data != NULL){
        VersionBinary *new_version_binary = createVersionBinary(version_description, user_data);
        Version* new_versoin_node = createVersion(new_version_binary);
        int check = addNewVersionToVersionList(head, new_versoin_node);
        if(check == 0){
            project->versions_count++;
            strcpy(project->project_hash, new_version_binary->version_hash);
            project->latest_update = new_version_binary->creation_date;
            saveProjectWithVersions(project, *head);

        }
        free(new_version_binary);
        free(new_versoin_node);
    }
    free(user_data);
    
}

void vcPull(char* file_name, unsigned int version_id, Version* head){
    Version* temp = getVersionWithId(head, version_id);

    if(temp != NULL){
        writeStructToFile(file_name, temp->version_binary->user_data, temp->version_binary->user_data_size);
        printf("Successfull pushed");
    }
    else
    {
        printf("Version with id: %d do not exist", version_id);
    }
    
}

