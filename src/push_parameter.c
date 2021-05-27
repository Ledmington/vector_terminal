#include <stdio.h>

#include "parameters.h"

void push_parameter(COMMAND* cmd, PARAMETER* new_param) {
	/*
		This is in fact the push of the data structure for PARAMETERs
	*/
	if(new_param == NULL ||
        new_param->short_name == NULL) return;

	if(cmd->first_param == NULL) {
        cmd->first_param = new_param;
    }
    else{
        cmd->last_param->next_param = new_param;
    }

    cmd->last_param = new_param;
    new_param->next_param = NULL;
}