#include "command_set.h"
#include "../error.h"

bool want_to_quit = false;

bool quit(INPUT_STRING* input_str){
    // Causes the program to exit
	
    error = no_error;
    want_to_quit = true;
    return true;
}