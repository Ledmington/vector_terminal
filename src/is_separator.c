#include <string.h>

#include "utils.h"
#include "command_set/csv_utils.h"

bool is_separator(char c){
    /*
        Checks if a character is a separator.

        Returns true if it is,
        false otherwise.
    */

    return strchr(sep, c) != NULL;
}