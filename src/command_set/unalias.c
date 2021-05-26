#include <stdio.h>

#include "alias_utils.h"
#include "../error.h"

bool unalias(INPUT_STRING* input_str){
	/*
		Removes an already set alias.
	*/

	ALIAS* tmp = search_alias(input_str->params[0]);
	if(tmp == NULL){
		#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
		print_error(help_msg);
		#endif
		return false;
	}
	else{
		remove_alias(tmp);
		return true;
	}

	return true;
}