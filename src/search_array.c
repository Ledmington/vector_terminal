#include <string.h>

#include "commands.h"
#include "error.h"

ARRAY* search_array(char* name) {
    /*
        Looks for the array with the given name in the ARRAY linked list.
        Returns a pointer to the array if it exists,
        NULL otherwise.
        (The variable 'error' is set properly)
    */


    ARRAY* array_tmp = array_list;

    while(array_tmp != NULL) {

        if(strcmp(array_tmp->name, name) == 0) {
        	error = array_already_existing;
            return array_tmp;
        }

        array_tmp = array_tmp->next_array;
    }

    error = array_not_found;
    return NULL;
}