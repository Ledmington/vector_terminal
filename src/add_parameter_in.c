#include <stdlib.h>
#include <stdio.h>

#include "parameters.h"
#include "command_set/csv_utils.h"
#include "api.h"
#include "utils.h"

PARAMETER* add_parameter_in(COMMAND *cmd, const bool mandatory, const char* short_name, const char* long_name, const unsigned short int numbers_required, const char* description) {
    /*
        The new parameter structure is added at the tail of the command's parameters queue.
        In fact, that queue is a linked list managed as a queue.

        A pointer to the new PARAMETER structure is returned.
    */

    PARAMETER *tmp = (PARAMETER*) malloc(sizeof(PARAMETER));
    if(tmp == NULL) {
    	char str[maxin];
        sprintf(str, "ERROR: cannot store \'%s\' | \'%s\' parameter for command \'%s\' in memory\n", short_name, long_name, cmd->name);
        appout(str);
        return NULL;
    }

    tmp->mandatory = mandatory;

    if(short_name == NULL) {
    	tmp->short_name = new_string("(none)");
    }
    else{
    	tmp->short_name = new_string(short_name);
    }

    if(long_name == NULL) {
    	tmp->long_name = new_string("(none)");
    }
    else{
    	tmp->long_name = new_string(long_name);
    }

    tmp->numbers_required = numbers_required;

    tmp->description = new_string(description);

    push_parameter(cmd, tmp);
    return tmp;
}