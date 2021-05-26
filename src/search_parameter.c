#include <stdio.h>
#include <string.h>

#include "parameters.h"
#include "error.h"

PARAMETER* search_parameter(COMMAND* cmd, char* name) {
    /*
        Looks for the parameter corresponding to the given name
        (no matter if it's the short or the long name)
        in all the parameters list of the COMMAND structure given.

        Returns a pointer to the PARAMETER structure if that exists,
        NULL otherwise.
        (The variable 'error' is set properly)
    */


    PARAMETER* param_tmp = cmd->first_param;

    while(param_tmp != NULL) {
        if(strcmp(param_tmp->short_name, name)==0 || strcmp(param_tmp->long_name, name)==0) {
        	error = no_error;
            return param_tmp;
        }
        param_tmp = param_tmp->next_param;
    }

    error = parameter_not_found;
    return NULL;
}