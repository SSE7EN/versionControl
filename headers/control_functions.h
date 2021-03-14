#ifndef CONTROL_FUNCTIONS_H
#define CONTROL_FUNCTIONS_H

#include "../headers/structures.h"

/**
 * @brief function initializes version control
 **/
/* TODO @kswierzy: there is a difference between "void vcInit()" and "void vcInit(void).
Functions without arguments should allways be declared as void fcn(void). */
void vcInit();

/**
 * @brief shows project info from config
 */
void vcProjectInfo(Project* proj);

/**
 * @brief creates new project
 */
void vcCreateProject(char* project_name, char* project_description);


/**
 * @brief get all projects
 */

void vcGetProjects();

/**
 * @brief change project
 */
void vcCheckout(char* project_name);

/**
 * @brief push changes
 */
void vcPush(char* push_file, char* version_description, Project* project, Version** head);

/**
 * @brief loads version with the given id
 */
void vcPull(char* file_name, unsigned int version_id, Version* head);

/**
 * @brief load Cofig
 */
Config* loadConfig();

/**
 * @brief load project with versions
 */
void loadProjectWithVersions(Config* config, Project** project, Version** vers);

/**
 * @brief save project with versions
 */
void saveProjectWithVersions(Project* project, Version* head);

/**
 * @brief show all project versions
 */
void vcGetVersions(Version* head);

/**
 * @brief check if destination was initialized
 */
int checkIfInit();

#endif

