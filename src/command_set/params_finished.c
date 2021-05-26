#include "command_set.h"

// Utility function for command implementation
bool params_finished(unsigned int index, INPUT_STRING* input_str){
	/**
	* Returns true if a parameter at the given index does not exist.
	*/
    return index >= input_str->num_parameters;
}