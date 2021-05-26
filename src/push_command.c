#include <stdio.h>

#include "commands.h"

unsigned int NUM_COMMANDS = 0;

COMMAND* command_set = NULL;

COMMAND* command_set_end = NULL;

void push_command(COMMAND* cmd) {
	/*
		This is in fact the push of the data structure for COMMANDs
	*/
	if(cmd == NULL) return;

	if(command_set == NULL) {
        command_set = cmd;
    }
    else{
        command_set_end->next_cmd = cmd;
    }

    command_set_end = cmd;
    cmd->next_cmd = NULL;

    NUM_COMMANDS++;
}