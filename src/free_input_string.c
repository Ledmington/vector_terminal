#include <stdlib.h>

#include "input_string_utils.h"

void free_input_string(INPUT_STRING* tmp) {
	//Releases the memory of an INPUT_STRING structure
	for(unsigned int i=0; i<tmp->num_parameters; i++) {
		free(tmp->params[i]);
	}
	free(tmp->params);
	free(tmp);
}