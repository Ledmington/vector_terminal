#include <stdio.h>

#include "command_set.h"
#include "../commands.h"
#include "../error.h"

extern unsigned int NUM_ARRAYS;

bool destroy(INPUT_STRING* input_str){
    /*
        Deletes an existing array
    */
    unsigned int current_param = 0;

    ARRAY* array_tmp = search_array(input_str->params[current_param]);
    if (array_tmp == NULL) {
        error = array_not_found;
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        print_error(help_msg);
        #endif
        return false;
    }
    current_param++;

    if(array_list == NULL || array_tmp == NULL){
        error = array_not_found;
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        print_error(help_msg);
        #endif
        return false;
    }

    if(array_tmp == array_list){
        array_list = array_list->next_array;
        free_array(array_tmp);
        error = no_error;
        return true;
    }

    ARRAY* prev = array_list;
    while(prev != NULL && prev->next_array != array_tmp){
        prev = prev->next_array;
    }
    if(prev == NULL){
        error = array_not_found;
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        print_error(help_msg);
        #endif
        return false;
    }

    prev->next_array = array_tmp->next_array;
    free_array(array_tmp);

    NUM_ARRAYS--;

    error = no_error;
    return true;
}