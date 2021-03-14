#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Structure of binary file version
 * 
 * used to save, read and create data
 */
typedef struct VersionsBinarys{ /* TODO @kswierzy: VersionBinarys? */
    int user_data_size; /**< size of the user_data (size = length)*/ /* TODO @kswierzy: size types should be unsigned. */
    time_t creation_date; /**< creation time of version*/  
    char version_description[80]; /**< the version descripion*/ /* TODO @kswierzy: good c programming practice tells us to first define numbers
                                                                (ex. #define STRUCTURE_MAXVERSION_DESCRIPTION_LENGTH 80
                                                                and then use them in code. Otherwise they are called "magic numbers". */
    char version_hash[33]; /**< the hash is used to check if the file was changed*/
    char user_data[]; /**< pointer to the user data in binary*/
}VersionBinary;

/**
 * @brief function that creates binary version from Version
 */
VersionBinary* createVersionBinary(char *version_description, char *user_data);

/**
 * @brief display VersionBinary
 */
void displayVersionBinary(VersionBinary* version_binary);

/**
 * @brief display VersionBinary with id
 */
void displayVersionBinaryWithId(VersionBinary *version_binary, unsigned int id);



/**
 * @brief Structure of file version 
*/
typedef struct Versions
{
    struct Versions *next; /**< pointer to the next verion*/
    VersionBinary *version_binary; /**< the binary verision */
    
}Version;

/**
 * @brief Display Version
 */
void displayVersion(Version* version);

/**
 * @brief function that creates version out of VersionBinary
 */
Version* createVersion(VersionBinary* version_binary);

/**
 * @brief function that returns the pointer to the last node of the Version list
 */

/* TODO @kswierzy: Function parameters should be documented with @param:

/**
 * @brief function that returns the pointer to the last node of the Version list
 *
 * @param head Pointer to the first node of version list.
 */


Version** getLastVersionNode(Version** head /** pointer to the first node of version list*/);

/**
 * @brief get verion with the given id
 */
Version* getVersionWithId(Version* head, unsigned int version_id);


/**
 * @brief function that adds the given version as the last node to the version list
 */
void addVersionToVersionList(Version **head /**< pointer to the first node of version list*/, Version *version_to_add );

/**
 * @brief function that adds new version to version list
 */
int addNewVersionToVersionList(Version **head /**< pointer to the first node of version list*/, Version *version_to_add );

/**
 * @brief function that recovers user binary data from Version
 */
void* getUserDataFromVersion(Version *version /**< version to recovers user binary data from*/);

/**
 * @brief function that free the memory used by Version list
*/
void freeMemoryFromVersionList(Version** head /**< pointer to the first node of version list*/);

/**
 * @brief Structure of Project
 */
typedef struct Projects
{
    int versions_count; /**< count of all project versions */
    char project_name[20]; /**< name of the project */
    char project_description[80]; /**< description of the project */
    char project_hash[33]; /**< newest version hash */
    time_t latest_update; /**< latest update*/  
    
}Project;

/**
 * @brief Display Project
 */
void displayProject(Project* project);

/**
 * @brief function that creates Project
 */
Project* createProject(char* project_name, char* project_description);

/**
 * @brief function that free the memory used by Version list
*/
void freeMemoryFromProject(Project* proj);


/**
 * @brief Structure of config
 */
typedef struct Configs{
    char project_name[20]; /**< name of project aka branch already in "control"*/
    char version_description[80]; /**<description of latest version */
}Config;

/**
 * @brief Display Config
 */
void displayConfig(Config *config);

/**
 * @brief creates empty config to initialize vc
 */
Config* createEmptyConfig();

/**
 * @brief Create Config from Project
 */
Config* createConfigFromProject(Project* project);

#endif