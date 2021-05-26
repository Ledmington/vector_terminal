#include <stdio.h>
#include <stdlib.h>

#include "input_string_utils.h"

INPUT_STRING* reduce_input_string(INPUT_STRING* input_str) {
	//Deletes the first string of the given structure
	if(input_str == NULL) {
		return NULL;
	}

	if(input_str->num_parameters == 0) {
		return input_str;
	}

	free(input_str->params[0]);
	for(unsigned int i=0; i<input_str->num_parameters-1; i++) {
		input_str->params[i] = input_str->params[i+1];
	}
	input_str->num_parameters--;
	input_str->params = (char**) realloc( input_str->params, (input_str->num_parameters) * sizeof(char*) );
	return input_str;
}