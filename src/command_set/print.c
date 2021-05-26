#include <stdio.h>
#include <string.h>

#include "command_set.h"
#include "../utils.h"
#include "../commands.h"
#include "../error.h"
#include "../api.h"

bool print(INPUT_STRING* input_str){
    /*
        Prints some elements of the specified existing array
    */

    unsigned int current_param = 0;
    bool with_index = false;

    ARG input;

    ARRAY* arr = search_array(input_str->params[current_param]);
    if (arr == NULL) {
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        print_error(help_msg);
        #endif
        return false;
    }

    current_param++;

    input.ref = arr;
    input.x[0] = 0;
    input.x[1] = input.ref->size-1;

    for(; !params_finished(current_param, input_str); current_param++){
        if(!strcmp(input_str->params[current_param], "-i") || !strcmp(input_str->params[current_param], "--index")){
            with_index = true;
            continue;
        }
        else if(!strcmp(input_str->params[current_param], "-r") || !strcmp(input_str->params[current_param], "--range")){
            if(params_finished(current_param+2, input_str)){
            	error = too_few_parameters;
                #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
                print_error(help_msg);
                #endif
                return false;
            }

            input.x[0] = str_to_uint(input_str->params[current_param+1]);
            if(input.x[0] == 0 && error != no_error){
                #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
                print_error(help_msg);
                #endif
                return false;
            }

            input.x[1] = str_to_uint(input_str->params[current_param+2]);
            if(input.x[1] == 0 && error != no_error){
                #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
                print_error(help_msg);
                #endif
                return false;
            }

            current_param += 2;
        }
        else{
            error = parameter_not_found;
            #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        	print_error(help_msg);
            #endif
        	return false;
        }

    }

    print_range(&input, with_index);

    error = no_error;
    return true;
}

void print_range(ARG* arr, bool index){
    /*
        arr->ref is the pointer to the array to be printed
        arr->x[0] is used as the starting index
        arr->x[1] is used as the ending index
    */
    char tmp[100];

    for(unsigned int i=arr->x[0]; (i<=arr->ref->size-1 && i<=arr->x[1]); i++){
        if(index){
            sprintf(tmp, "%s[%u] = ", arr->ref->name, i);
            appout(tmp);
        }
        sprintf(tmp, "%d\n", arr->ref->ptr[i]);
        appout(tmp);
    }
}