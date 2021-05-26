#include <stdlib.h>
#include <stdio.h>

#include "input_string_utils.h"
#include "utils.h"

INPUT_STRING* copy_input_string(INPUT_STRING* tmp) {
	//Creates and returns an exact copy of the given INPUT_STRING structure
	if(tmp == NULL) {
		return NULL;
	}

	INPUT_STRING* new_input = (INPUT_STRING*) malloc(sizeof(INPUT_STRING));

	new_input->num_parameters = tmp->num_parameters;

	new_input->params = (char**) malloc(new_input->num_parameters * sizeof(char*));

	for(unsigned int i=0; i<new_input->num_parameters; i++) {
		new_input->params[i] = new_string(tmp->params[i]);
	}

	return new_input;
}