#include <stdio.h> // NULL

#include "parameters.h"

void push_parameter(COMMAND* cmd, PARAMETER* param_tmp) {
	/*
		This is in fact the push of the data structure for PARAMETERs
	*/
	if(param_tmp == NULL) return;

	if(cmd->first_param == NULL) {
        cmd->first_param = param_tmp;
    }
    else{
        cmd->last_param->next_param = param_tmp;
    }

    cmd->last_param = param_tmp;
    param_tmp->next_param = NULL;
}