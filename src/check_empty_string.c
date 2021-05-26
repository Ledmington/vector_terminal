#include <stdbool.h>

#include "utils.h"

bool check_empty_string(const char* str){
    /*
        Checks whether the given string is NULL or empty.
        Returns true if str is empty,
        false otherwise.
    */
    return str==NULL || str[0]=='\0';
}