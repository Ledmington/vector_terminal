#include <stdlib.h> // free
#include <stdio.h> // NULL

#include "commands.h"
#include "parameters.h"

void delete_command(COMMAND* cmd) {
	/*
		This is just the free of a COMMAND
	*/
	if(cmd == NULL) return;

	while(cmd->first_param != NULL) {
        delete_parameter( pop_parameter(cmd) );
    }

    free(cmd->name);
    free(cmd->description);
    free(cmd);
}