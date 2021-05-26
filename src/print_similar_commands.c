#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0

#include <stdio.h>

#include "commands.h"
#include "command_set/csv_utils.h" // maxdiff

void print_similar_commands(char* str) {
	/*
		Searches in the COMMANDs queue all the similar commands, and prints them.
		A command is considered similar if countCharDiff(str, COMMAND_NAME) <= MAX_DIFFERENT_CHARS
	*/
	COMMAND* cmd = command_set;
	bool found = false;

	while(cmd != NULL) {
		if(count_char_diff(str, cmd->name) <= maxdiff) {
			if(found == false) {
				found = true;
				printf("\nDid you mean :\n");
			}
			printf(" \'%s\'\n",cmd->name);
		}

		cmd = cmd->next_cmd;
	}

	printf("\n");

	return;
}
#endif