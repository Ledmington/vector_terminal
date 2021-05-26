#include <stdio.h>

#include "alias_utils.h"
#include "../error.h"

bool alias(INPUT_STRING* input_str){
	/*
		If called without parameters, it prints all the aliases.
		If called with two valid strings:
			it checks that the first isn't already defined
			creates a new alias with the two strings
	*/

	//No parameters
	if(input_str->num_parameters == 0){
		#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
		print_alias_list();
		#endif
		return true;
	}

	//Just one parameter
	if(input_str->num_parameters == 1){
		error = too_few_parameters;
		#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
		print_error(help_msg);
		#endif
		return true;
	}

	if(search_alias(input_str->params[0]) == NULL){
		//If the first string is not already set as alias
		add_alias(input_str->params[0], input_str->params[1]);
		return true;
	}
	else{
		//If the first string is already set as alias
		#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
		print_error(help_msg);
		#endif
		return false;
	}

	return true;
}