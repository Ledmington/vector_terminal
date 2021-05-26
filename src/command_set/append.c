#include <stdio.h>
#include <stdlib.h>

#include "command_set.h"
#include "../utils.h"
#include "../commands.h"
#include "../error.h"
#include "../parameters.h"

bool append(INPUT_STRING* input_str){
    /*
        Requires the names of two existing arrays.
        If no parameter is added, the command appends the content
        of the second array to the first.
        If '-n' specified, a new array with the specified name is
        created.
    */
    unsigned int current_param = 0;
    COMMAND* cmd = search_command("append");

    ARRAY* first = search_array(input_str->params[current_param]);
    if(first == NULL){
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        print_error(help_msg);
        #endif
        return false;
    }

    current_param++;

    ARRAY* second = search_array(input_str->params[current_param]);
    if(second == NULL){
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        print_error(help_msg);
        #endif
        return false;
    }

    current_param++;

    //Without "-n"
    if(params_finished(current_param, input_str)){

        int* tmp = (int*) calloc(first->size+second->size, sizeof(int));
        set_values_at(tmp, 0, first->ptr, first->size);

        set_values_at(tmp, first->size, second->ptr, second->size);
        
        free(first->ptr);
        first->ptr = tmp;
        first->size += second->size;
        return true;
    }

    if(search_parameter(cmd, input_str->params[current_param]) != search_parameter(cmd, "-n")){
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        print_error(help_msg);
        #endif
        return false;
    }

    current_param++;
    
    if(params_finished(current_param, input_str)){
        error = parameter_not_found;
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        print_error(help_msg);
        #endif
        return false;
    }

    ARRAY* new_array = (ARRAY*) malloc(sizeof(ARRAY));

    new_array->name = new_string(input_str->params[current_param]);
    new_array->size = first->size + second->size;
    new_array->ptr = (int*) calloc(new_array->size, sizeof(int));
    set_values_at(new_array->ptr, 0, first->ptr, first->size);
    set_values_at(new_array->ptr, first->size, second->ptr, second->size);

    new_array->next_array = array_list;
    array_list = new_array;

    return true;
}