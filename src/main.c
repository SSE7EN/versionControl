/* TODO @kswierzy: it is better (cleaner) to include header files from one point
    without "../". This could be done in Makefile with -I. */
/* TODO @kswierzy: header files are frequently placed in src, include or inc directory. */
#include "../headers/files_functions.h"
#include  "../headers/structures.h" /* TODO @kswierzy: one space to much. */
#include "../headers/control_functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
    vc_Init,
    vc_SaveVersion,
    vc_ProjectInfo,
    vc_CreateProject,
    vc_GetProjects,
    vc_Checkout,
    vc_Push,
    vc_Pull,
    vc_GetVersions,
    help /* TODO @kswierzy: vc_help. */
}Control;

void program(Control control, char* file_name, char* description, char* name, unsigned int version_id){
    if(control == vc_Init){
        vcInit();
    }
    else{
        if(checkIfInit() == 0){
            Project* proj = NULL;
            Version* version_head = NULL;
            Config* config = loadConfig();
            loadProjectWithVersions(config, &proj, &version_head);

            switch(control){
                case vc_ProjectInfo:
                    vcProjectInfo(proj);
                    break;
                case vc_CreateProject:
                    vcCreateProject(name, description);
                    break;
                case vc_GetProjects:
                    vcGetProjects();
                    break;
                case vc_Checkout:
                    vcCheckout(name);
                    break;
                case vc_Push:
                    vcPush(file_name, description, proj, &version_head);
                    break;
                case vc_Pull:
                    vcPull(file_name, version_id, version_head);
                    break;
                case vc_GetVersions:
                    vcGetVersions(version_head);
                    break;
                default:
                    printf("Not implemented sorry :/");
                    break;
                
            }
            freeMemoryFromVersionList(&version_head);
            free(proj);
            free(config);
        }
        else printf("Destination was not initialized, do vcInit"); /* TODO @kswierzy: curly braces. */
    }   
}

int main(int argc, char* argv[]){
    /* TODO @kswierzy: declare variables immediately before use. */
    /* TODO @kswierzy: initialise variables if there can be a path where they aren't initialised.  */
    Control control;
    char* description; /* TODO @kswierzy: what if description is NULL or description is not provided by user (and description is not NULL)? */
    unsigned int version_id = 0;
    char* file_name;
    char* name;

    /* TODO @kswierzy: i == 0 if execution path so it must not be checked. */
    for(int i = 0; i < argc; i++){

        /* TODO @kswierzy: if - else if - else is much better than continue.
        "continue" statement shouldn't be used.*/
        if(strcmp("vcInit", argv[i]) == 0){
            control = vc_Init;
            continue;
        }
        if(strcmp("vcSaveVersion", argv[i]) == 0){
            control = vc_SaveVersion;
            continue; /* TODO @kswierzy: remove new line. */
            
        }
        if(strcmp("vcProjectInfo", argv[i]) == 0){
            control = vc_ProjectInfo;
             continue;
       }
        if(strcmp("vcCreateProject", argv[i]) == 0){
            control = vc_CreateProject;
            continue;
        }    
        if(strcmp("vcGetProjects", argv[i]) == 0){
            control = vc_GetProjects;
            continue;
        }
        if(strcmp("vcCheckout", argv[i]) == 0){
            control = vc_Checkout;
            continue;
        }        
        if(strcmp("vcPush", argv[i]) == 0){
            control = vc_Push;
            continue;
        }
        if(strcmp("vcPull", argv[i]) == 0){
            control = vc_Pull;
            continue;
        }    
        if(strcmp("vcGetVersions", argv[i]) == 0){
            control = vc_GetVersions;
            continue;
        }
        if(strcmp("-help", argv[i]) == 0){
            control = help;
            continue;
        }
        if(strcmp("-d", argv[i]) == 0){
            description = argv[i + 1]; /* TODO @kswierzy: what if i + 1 does not exists? */
            i++;
            continue;
        }    
        if(strcmp("-n", argv[i]) == 0){
            name = argv[i+1];
            i++;
            continue;
        }
        if(strcmp("-id", argv[i]) == 0){
            version_id = strtol(argv[i + 1], NULL, 10);
            i++;
            continue;
        }
        if(strcmp("-f", argv[i]) == 0){
            file_name = argv[i + 1];
            i++;
            continue;
        }

    }
    if(argc >= 2){
        program(control,file_name, description, name, version_id);

    }
    else printf("\n Not valid argument, see -help"); /* TODO @kswierzy: use curly braces. */


    return 0; /* TODO @kswierzy: negativ return codes if something went wrong. */
}

