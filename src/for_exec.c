#include <string.h> // strstr

#include "commands.h"
#include "input_string_utils.h"
#include "utils.h"
#include "error.h"
#include "command_set/alias_utils.h" // check_aliases

bool for_exec(INPUT_STRING* input_str) {
	/*
		The first parameter is the number of iterations.
		After that, for each iteration, the command string is 
		given to the command function
	*/

	INPUT_STRING* tmp_input = copy_input_string(input_str);

	unsigned int num_iterations = str_to_uint(tmp_input->params[0]);
	if(error != no_error) {
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
		print_error(help_msg);
        #endif
		return false;
	}

	//deleting number of iterations
	reduce_input_string(tmp_input);

	/*
    	Checking if the user is calling the command unalias
    	THIS IS A BAD FEATURE
    	IT'S LIKE PUTTING MAGIC NUMBERS
    */
    if(strstr(tmp_input->params[0], "unalias") != tmp_input->params[0]) {
    	//Substituting all the aliases found in the string
    	tmp_input->params[0] = check_aliases(tmp_input->params[0]);
    }

    //Setting the command, if it exists
    COMMAND* cmd = search_command(tmp_input->params[0]);
	if(cmd == NULL) {
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
		print_error(help_msg);
        #endif
		return false;
	}

	//deleting the command name
	reduce_input_string(tmp_input);

	//Checking the correct number of parameters
    if(enough_parameters(cmd, tmp_input) == false) {
    	return false;
    }

	for(unsigned int i=0; i<num_iterations; i++) {
		printf("Iteration %u:\n",i+1);

		bool result = cmd->command_ptr(tmp_input);

		if(result == false && i != num_iterations-1) {
			printf("\n ------\n");
		}

	}

	free_input_string(tmp_input);
	/*
		No need to releases the memory for input_str
		In the recursive calls, each function releases the memory
		that it has copied, not the original one.
	*/

	return true;
}