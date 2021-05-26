#include <stdio.h> // NULL

#include "parameters.h"

PARAMETER* pop_parameter(COMMAND* cmd) {
	/*
		This is in fact the pop of the data structure for PARAMETERs
	*/
	if(cmd == NULL) return NULL;
	if(cmd->first_param == NULL) return NULL;

	if(cmd->last_param == cmd->first_param) {
        cmd->last_param = NULL;
    }

    PARAMETER* param_tmp = cmd->first_param->next_param;

    PARAMETER* prm = cmd->first_param;

    cmd->first_param = param_tmp;

    return prm;
}