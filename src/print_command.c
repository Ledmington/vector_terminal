#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0

#include <stdio.h>
#include <stdlib.h>

#include "commands.h"
#include "api.h"

void print_command(COMMAND *cmd, bool with_parameters) {
    /*
        Prints all the informations about the given command
        and all its parameters.
    */
    unsigned int size = 300;
    char* tmp = (char*) calloc(size, sizeof(char));
    sprintf(tmp, " %-10s\t%s\n", cmd->name, cmd->description);
    appout(tmp);
    free(tmp);

    if(!with_parameters) return;

    tmp = (char*) calloc(size, sizeof(char));

    PARAMETER *param_tmp = cmd->first_param;
    if(param_tmp == NULL) {
        free(tmp);
        appout("\t(no parameters required)\n");
    }
    else{
    	while(param_tmp != NULL) {

            appout("\t");
            if(param_tmp->mandatory == true) {
                appout("**");
            }

            if(param_tmp->short_name != NULL) {
            	sprintf(tmp, "%-16s\t",param_tmp->short_name);
            }
            else{
            	sprintf(tmp, "%-16s\t","(none)");
            }
            appout(tmp);
            free(tmp);
            tmp = (char*) calloc(size, sizeof(char));

            if(param_tmp->long_name != NULL) {
            	sprintf(tmp, "%-20s\t",param_tmp->long_name);
            }
            else{
            	sprintf(tmp, "%-20s\t","(none)");
            }
            appout(tmp);
            free(tmp);
            tmp = (char*) calloc(size, sizeof(char));

            sprintf(tmp, "\t%s\n",param_tmp->description);
            appout(tmp);
            free(tmp);
            tmp = (char*) calloc(size, sizeof(char));

            param_tmp = param_tmp->next_param;
        }
        free(tmp);
    }
}
#endif