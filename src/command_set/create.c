#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "command_set.h"
#include "csv_utils.h"
#include "../utils.h"
#include "../api.h"
#include "../commands.h"
#include "../error.h"
#include "../parameters.h"

ARRAY* array_list = NULL;

unsigned int NUM_ARRAYS = 0;

bool create(INPUT_STRING* input_str){
    /*
        Creates a new array
        The correct order for parameter is the following:
        create ARRAY_NAME ARRAY_SIZE [-s x] [-sf x y]

        Example:
        the command:
        'create NEW 50 -s 0 -sf 10 1'
        creates a new array named 'NEW',
        of size 50,
        automatically setting all its elements to 0,
        then setting elements starting from index 10 to values 1,1,1,1,1,1...

        This command controls each parameter separately in a sequential order.
        For example:
        'create NEW 50 -s 1 -sf 5 2 -s 4'
        creates a new array named 'NEW',
        of size 50,
        automatically setting all its elements to 1,
        setting elements starting from index 5 to values 2,2,2,2,2,2...
        then setting all its elements to 4.

        So after this command, NEW will contain only 4's
    */

    unsigned int current_param = 0;

    // Retrieving maximum array size
    CSV* csv_maxarr = search_csv("maxarr");
    if(csv_maxarr == NULL){
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        appout("Internal error: maxarr not found\n");
        #endif
        return false;
    }

    // Asserting the first parameter is an existing array
    // Is this needed?
    if(search_array(input_str->params[current_param]) != NULL){
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        print_error(help_msg);
        #endif
        return false;
    }

    // New array's name cannot contain numbers 
    for(int i=0; i<strlen(input_str->params[current_param]); i++){
        if(isdigit(input_str->params[current_param][i])){
        	error = invalid_name;
            #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
            print_error(help_msg);
            #endif
            return false;
        }
    }

    // Creating new array
    ARRAY* new_array = (ARRAY*) malloc(sizeof(ARRAY));
    if (new_array == NULL) {
        error = out_of_memory;
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        print_error(help_msg);
        #endif
        return false;
    }

    // Copying the name
    new_array->name = (char*) calloc(strlen(input_str->params[current_param])+1, sizeof(char));
    strncpy(new_array->name, input_str->params[current_param], strlen(input_str->params[current_param]));

    current_param++;

    // Reading new array's size
    new_array->size = str_to_uint(input_str->params[current_param]);
    if(error != no_error){
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        print_error(help_msg);
        #endif
        return false;
    }

    if(new_array->size == 0){
        error = conversion_failed;
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        print_error(help_msg);
        #endif
        return false;
    }

    // Checking that size is not too big
    if(new_array->size > csv_maxarr->actual_value.x){
    	error = array_size_too_big;
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        print_error(help_msg);
        #endif
        return false;
    }

    // Allocating array
    new_array->ptr = (int*) calloc(new_array->size, sizeof(int));
    if (new_array->ptr == NULL) {
        error = out_of_memory;
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        print_error(help_msg);
        #endif
        return false;
    }

    // Checking other parameters
    COMMAND* cmd = search_command("create");

    current_param++;

    for(; !params_finished(current_param, input_str); current_param++){
        PARAMETER* param_tmp = search_parameter( cmd, input_str->params[current_param] );
        if(param_tmp == NULL){
            #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
            print_error(help_msg);
            #endif
            return false;
        }

        if(current_param == input_str->num_parameters-1){
        	error = number_needed;
            #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
            print_error(help_msg);
            #endif
            return false;
        }

        current_param++;
        ARG new_input;
        new_input.ref = new_array;

        // Reading additional numbers required by the parameter
        for(int j=0; j<param_tmp->numbers_required; j++){
            if(!params_finished(current_param + j, input_str)){
                // Reading the integer
                new_input.x[j] = str_to_int(input_str->params[current_param + j]);
                if(new_input.x[j] == 0 && error != no_error){
                    #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
                    print_error(help_msg);
                    #endif
                    return false;
                }
            }
            else{
            	error = too_few_parameters;
                #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
                print_error(help_msg);
                #endif
                return false;
            }
        }

        current_param += param_tmp->numbers_required-1;

        swap(&new_input.x[0], &new_input.x[1]);

        // Parameter "-s"
        if(param_tmp->numbers_required == 1) {
            set(&new_input);
        }
        // Parameter "-sf"
        else if(param_tmp->numbers_required == 2) {
            set_from(&new_input);
        }
    }

    new_array->next_array = array_list;
    array_list = new_array;

    NUM_ARRAYS++;

    error = no_error;
    return true;
}