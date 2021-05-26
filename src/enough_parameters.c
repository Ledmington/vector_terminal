#include <stdbool.h>

#include "commands.h"
#include "input_string.h"
#include "error.h"

bool enough_parameters(COMMAND* cmd, INPUT_STRING* input_str) {
	/*
		Returns true whether there are enough parameters in the given INPUT_STRING structure
		to have a correct behavior from the command.
	*/

	if(input_str->num_parameters < cmd->min_params) {
		error = too_few_parameters;
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
		print_error(help_msg);
        #endif
		return false;
	}
	else if(input_str->num_parameters > cmd->max_params) {
		error = too_many_parameters;
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
		print_error(help_msg);
        #endif
		return false;
	}
	else{
		error = no_error;
		return true;
	}
}