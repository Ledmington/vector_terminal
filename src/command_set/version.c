#include <stdbool.h>

#include "command_set.h"
#include "../error.h"
#include "../api.h"
#include "../utils.h"

bool version (INPUT_STRING* input_str) {
	/*
		Prints the string representing the version number of the terminal
		and the license message.
	*/
	const char* ver = new_string(
		"Vector Terminal v0.3.4\n"
		"Copyright (C) 2021  Ledmington\n"
    	"This program comes with ABSOLUTELY NO WARRANTY and is free software.\n"
    	"For details, see the file \"LICENSE\".\n");

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