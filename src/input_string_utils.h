#pragma once

#include "input_string.h"

//Releases the memory of an INPUT_STRING structure
void free_input_string(INPUT_STRING* tmp);

//Creates and returns an exact copy of the given INPUT_STRING structure
INPUT_STRING* copy_input_string(INPUT_STRING* tmp);

/*
    Prepares the INPUT_STRING structure to be passed to the command function.
*/
INPUT_STRING* set_command_line(char* str);

//Deletes the first string of the given structure
INPUT_STRING* reduce_input_string(INPUT_STRING* input_str);