#ifndef HISTORY_H_INCLUDED
#define HISTORY_H_INCLUDED

#include <stdbool.h>

#include "history_string.h"
#include "../input_string.h"

//Pointer to the first element in the history
HISTORY_STRING* first;

/*
    Pointer to the last element in history
    (even if this is used as a stack, i need two pointers in order to print all the list
    from the very first structure)
*/
HISTORY_STRING* last;

bool history(INPUT_STRING* input_str);

#endif