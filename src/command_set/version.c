#include <stdbool.h>

#include "command_set.h"
#include "../error.h"
#include "../api.h"
#include "../utils.h"

bool version (INPUT_STRING* input_str) {
	/*
		Prints the string representing the version number of the terminal.
	*/
	const char* ver = new_string("Vector Terminal v0.3.1\n");

	if (input_str->num_parameters != 0) {
		error = too_many_parameters;
		#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
		print_error(help_msg);
		#endif
		return false;
	}

	#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
	appout(ver);
	#endif

	return true;
}