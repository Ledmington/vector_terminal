#pragma once

#include <stdbool.h>

#include "command.h"
#include "parameter.h"

PARAMETER* add_parameter_in (COMMAND* cmd, const bool mandatory, const char* short_name, const char* long_name, const unsigned short int numbers_required, const char* description);

// Function that frees the memory dinamically allocated for the creation of the PARAMETER structure
void delete_parameter(PARAMETER* param_tmp);

// Function that adds a new parameter at the end of the parameters' queue
void push_parameter(COMMAND* cmd, PARAMETER* param_tmp);

// Function that removes the structure at the top of the parameters' queue
PARAMETER* pop_parameter(COMMAND* cmd);

// Looks for a parameter with the given name in the command's parameters list
PARAMETER* search_parameter(COMMAND* cmd, char* name);