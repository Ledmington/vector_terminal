#include <stdio.h>
#include <string.h>

#include "commands.h"

unsigned int NUM_COMMANDS = 0;

// Pointer to the first element
COMMAND* command_set = NULL;

// Pointer to the last element
COMMAND* command_set_end = NULL;

void push_command(COMMAND* cmd) {
	/*
		This is in fact the push of the data structure for COMMANDs
	*/
	if(cmd == NULL || cmd->name == NULL) return;

    // If list is empty
    if(command_set == NULL) {
        cmd->next_cmd = NULL;
        command_set = command_set_end = cmd;
        NUM_COMMANDS++;
        return;
    }

    // If cmd is "less" than command_set
    if(strcmp(cmd->name, command_set->name) < 0) {
        cmd->next_cmd = command_set;
        command_set = cmd;
        NUM_COMMANDS++;
        return;
    }

    // General case
    COMMAND* tmp_cmd = command_set;
    while(tmp_cmd->next_cmd != NULL &&
        strcmp(tmp_cmd->next_cmd->name, cmd->name) < 0) {
        tmp_cmd = tmp_cmd->next_cmd;
    }

    cmd->next_cmd = tmp_cmd->next_cmd;
    tmp_cmd->next_cmd = cmd;

    if(command_set_end->next_cmd == cmd) {
        command_set_end = cmd;
    }

    NUM_COMMANDS++;
}