#include <string.h>
#include <stdlib.h>

#include "utils.h"

char* new_string(const char* new){
    /*
        This function's use is to set easily the strings in structures.

        Dynamically allocates a new string and copies the content
        of "new" into it. Then the pointer to the new string
        is returned.
    */
    unsigned int len = new==NULL ? 0 : strlen(new);
    char* str = (char*) calloc(len+1, sizeof(char));
    if(new != NULL) strncpy(str, new, len);
    return str;
}