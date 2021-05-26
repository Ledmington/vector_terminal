#include <string.h>

#include "commands.h"
#include "error.h"

COMMAND* search_command(char* name) {
    /*
        Looks for the command corresponding to the given name in the
        command_set list.

        Returns the pointer to the COMMAND structure if that command exists,
        NULL otherwise.
        (The variable 'error' is set properly)
    */

    COMMAND* tmp = command_set;

    while(tmp != NULL) {
        if(strcmp(name, tmp->name) == 0) {
        	error = no_error;
            return tmp;
        }
        tmp = tmp->next_cmd;
    }

    error = command_not_found;
    return NULL;
}