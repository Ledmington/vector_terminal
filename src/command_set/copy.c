#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "command_set.h"
#include "../commands.h"
#include "../error.h"

bool copy(INPUT_STRING* input_str){
	/*
		Creates a new array that is an exact copy of an existing one.
	*/
	unsigned int current_param = 0;

    //The old array must exist
	ARRAY* old_arr = search_array(input_str->params[current_param]);
    if (old_arr == NULL) {
        error = array_not_found;
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        print_error(help_msg);
        #endif
        return false;
    }
    current_param++;

    //The new array must not exist
    if(search_array(input_str->params[current_param]) != NULL){
        error = array_already_existing;
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        print_error(help_msg);
        #endif
        return false;
    }
    current_param++;

	ARRAY* new_arr = (ARRAY*) malloc(sizeof(ARRAY));

	for(int i=0; i<strlen(input_str->params[current_param]); i++){
        if(isdigit(input_str->params[current_param][i])){
        	error = invalid_name;
            #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
            print_error(help_msg);
            #endif
            return false;
        }
    }

	new_arr->name = (char*) calloc(strlen(input_str->params[current_param])+1, sizeof(char));
    strncpy(new_arr->name, input_str->params[current_param], strlen(input_str->params[current_param]));

    new_arr->size = old_arr->size;

    new_arr->ptr = (int*) calloc(new_arr->size, sizeof(int));

    for(unsigned int i=0; i<new_arr->size; i++){
    	new_arr->ptr[i] = old_arr->ptr[i];
    }

    new_arr->next_array = array_list;
    array_list = new_arr;

	return true;
}