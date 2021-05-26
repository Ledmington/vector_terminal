#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"

bool check_space_string(const char* str){
    /*
        Checks whether the given string is composed only by "space" characters.
        Returns true if it is composed only by "space" characters,
        false otherwise.
    */
    for(unsigned int i=0; i<strlen(str); i++){
        if(!isspace(str[i])){
            return false;
        }
    }
    return true;
}