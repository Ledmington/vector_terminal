#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <stdbool.h>

#include "input_string.h"
#include "parameter.h"

/*
    Definition of the pointer to the function that holds the behavior of the command.

    Each command structure contains this pointer in order to write very small code for this operation
    (otherwise there would have been too many 'switch' constructs)
*/
typedef bool (*function_ptr)(INPUT_STRING *input_str);


//The structure that holds all the information about a command.
typedef struct command {

    /*
        The name of the command.
        It is case sensitive.
        (if 'help' is a valid command, 'HELP' is not)
    */
    char* name;

    //A description of the behavior of the command
    char* description;

    //The minimum number of parameters required to not receive an error
    unsigned int min_params;

    //The maximum number of parameters required to not receive an error
    unsigned int max_params;

    //Pointer to the head of the parameter's queue
    PARAMETER* first_param;

    //Pointer to the tail of the parameter's queue
    PARAMETER* last_param;

    //Pointer to the function that has the behavior specified by the command
    function_ptr command_ptr;

    //Pointer to the next command structure in the command_set list
    struct command *next_cmd;

} COMMAND;

#endif // COMMAND_H_INCLUDED