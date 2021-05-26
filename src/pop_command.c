#include <stdio.h>

#include "commands.h"

COMMAND* pop_command() {
	/*
		This is in fact the pop of the data structure for COMMANDs
	*/
    if(command_set == NULL) return NULL;

    if(command_set == command_set_end) {
        command_set_end = NULL;
    }
    COMMAND* cmd = command_set->next_cmd;

    COMMAND* tmp = command_set;

    command_set = cmd;

    NUM_COMMANDS--;

    return tmp;
}