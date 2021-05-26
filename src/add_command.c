#include "commands.h"

#include "command_set/csv_utils.h"
#include "api.h"
#include "utils.h"

#include <stdlib.h>

COMMAND* add_command(char* name, char* description, unsigned int min_params, unsigned int max_params, void* command_pointer) {
    /*
        The new command is added to the tail of the command_set queue.
        In fact, that queue is a linked list managed as a queue.

        A pointer to the new COMMAND structure is returned.
    */

    COMMAND *cmd = (COMMAND*) malloc(sizeof(COMMAND));
    if(cmd == NULL) {
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
    	char* tmp = (char*) calloc(maxin, sizeof(char));
        sprintf(tmp, "ERROR: cannot store \'%s\' command in memory.\n",name);
        appout(tmp);
        #endif
        return NULL;
    }

    cmd->name = new_string(name);

    cmd->description = new_string(description);

    cmd->min_params = min_params;
    cmd->max_params = max_params;

    cmd->first_param = NULL;
    cmd->last_param = NULL;

    cmd->command_ptr = command_pointer;

    push_command(cmd);
    return cmd;
}