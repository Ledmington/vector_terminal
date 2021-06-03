#pragma once

#include <stdbool.h>

#include "history_string.h"
#include "../input_string.h"

//Pointer to the first element in the history
HISTORY_STRING* history_first;

/*
    Pointer to the last element in history
    (even if this is used as a stack, i need two pointers in order to print all the list
    from the very first structure)
*/
HISTORY_STRING* history_last;

bool history(INPUT_STRING* input_str);