#include <stdio.h>

#include "command_set.h"
#include "../api.h"
#include "../error.h"

bool list(INPUT_STRING* input_str){
    /*
        Prints the list of all existing arrays    
    */
    char tmp[100];

    if(array_list == NULL){
        appout("\n Array list is currently empty...\n\n");
        return true;
    }

    ARRAY* array_tmp = array_list;
    while(array_tmp != NULL){
        sprintf(tmp, "Name: %s\nSize: %u\n\n", array_tmp->name, array_tmp->size);
        appout(tmp);

        array_tmp = array_tmp->next_array;
    }

    error = no_error;
    return true;
}