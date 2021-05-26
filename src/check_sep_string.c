#include <string.h>

#include "utils.h"

bool check_sep_string(const char* str){
    /*
        Checks whether the given string is composed only by characters in the CSV "separators".
        Returns true if it is composed only by separators,
        false otherwise.
    */
    for(unsigned int i=0; i<strlen(str); i++){
        if(!is_separator(str[i])){
            return false;
        }
    }
    return true;
}