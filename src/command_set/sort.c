#include <stdlib.h>

#include "command_set.h"
#include "../utils.h"
#include "../commands.h"
#include "../parameters.h"
#include "../error.h"

bool sort(INPUT_STRING* input_str){
    /*
        Sorts in the specified order an existing array
    */

	COMMAND* cmd = search_command("sort");
    unsigned int current_param = 0;

    ARRAY* vector = search_array(input_str->params[current_param]);
    if (vector == NULL) {
        error = array_not_found;
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        print_error(help_msg);
        #endif
        return false;
    }

    current_param++;

    // Pointer to the auxiliary array for merge sort
    int* aux;

    /*
        HARD-CODING THE STRINGS TO CHECK IS A BAD FEATURE, IT'S LIKE PUTTING MAGIC NUMBERS
    */
    if(params_finished(current_param, input_str)){
        aux = (int*) malloc(vector->size * sizeof(int));
        if (aux == NULL) {
            error = out_of_memory;
            #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
            print_error(help_msg);
            #endif
            return false;
        }
    	merge_sort(vector->ptr, aux, 0, vector->size-1);
        free(aux);
    	return true;
    }

    PARAMETER* param_tmp = search_parameter(cmd, input_str->params[current_param]);

    if(param_tmp == search_parameter(cmd, "-a")){
        aux = (int*) malloc(vector->size * sizeof(int));
        if (aux == NULL) {
            error = out_of_memory;
            #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
            print_error(help_msg);
            #endif
            return false;
        }
        merge_sort(vector->ptr, aux, 0, vector->size-1);
        free(aux);
    }
    else if(param_tmp == search_parameter(cmd, "-d")){
        aux = (int*) malloc(vector->size * sizeof(int));
        if (aux == NULL) {
            error = out_of_memory;
            #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
            print_error(help_msg);
            #endif
            return false;
        }
        merge_sort(vector->ptr, aux, 0, vector->size-1);
        reverse(vector->ptr, 0, vector->size-1);
        free(aux);
    }
    else{
    	error = parameter_not_found;
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        print_error(help_msg);
        #endif
        return false;
    }

    error = no_error;
    return true;
}