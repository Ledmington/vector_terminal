#include <stdio.h>
#include <stdlib.h>

#include "command_set.h"
#include "../utils.h"
#include "../error.h"
#include "../parameters.h"

void set(ARG* arg){
    /*
        arg->ref is the pointer to the ARRAY structure
        arg->x[0] here is used as the initial index
        arg->x[1] here is used as the value to be written in each position
    */
    arg->x[0] = 0;
    set_from(arg);
}

void set_from(ARG* arg){
    /*
        arg->ref is the pointer to the ARRAY structure
        arg->x[0] here is used as the initial index
        arg->x[1] here is used as the value to be written in each position
    */
    for(unsigned int i=arg->x[0]; i<(arg->ref->size); i++){
        arg->ref->ptr[i] = arg->x[1];
    }
}

bool set_values(INPUT_STRING* input_str){
    /*
        Allows the change the values contained in an existing array.
        The correct syntax is rigid.

        set arr VALUES -i INDEX
        'arr' is the name of the existing array
        'VALUES' are the values to be set from the given index (minimum:1, maximum:n)
        'INDEX' is the index where to start replacing the values (needs to be just one)
    */
    COMMAND* cmd = search_command("set");
    unsigned int current_param = 0;
    unsigned int count = 0;
    int* values = NULL;

    ARRAY* arr = search_array(input_str->params[current_param]);
    if (arr == NULL) {
        error = array_not_found;
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        print_error(help_msg);
        #endif
        return false;
    }
    current_param++;

    //Counting the valid values
    for(unsigned int j=0; j<input_str->num_parameters; j++){

        str_to_int(input_str->params[current_param+j]);

        if(error == no_error){
            //If valid integer
            count++;
        }
        else if(error == conversion_failed){
            //If not a valid integer
            if(search_parameter(cmd, input_str->params[current_param+j]) == search_parameter(cmd, "-i")){
                //If '-i' found
                values = (int*) malloc(count * sizeof(int));
                break;
            }
            else{
                //If not a parameter
                #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
                print_error(help_msg);
                #endif
                return false;
            }   
        }
        else{
            //If overflow or underflow occurred during conversion
            #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
            print_error(help_msg);
            #endif
            return false;
        }
    }

    //Filling the values
    for(unsigned int i=0; i<count; i++){
        values[i] = str_to_int(input_str->params[current_param+i]);
    }

    /*
        Here is guaranteed that '-i' has been already found in the string
        in position (current_param+count)
    */
    current_param += count+1;

    if(params_finished(current_param, input_str)){
        //If nothing after '-i'
        free(values);
        error = too_few_parameters;
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        print_error(help_msg);
        #endif
        return false;
    }

    unsigned int index = str_to_uint(input_str->params[current_param]);
    if(index==0 && error!=no_error){
        //If no valid unsigned integer after '-i'
        free(values);
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        print_error(help_msg);
        #endif
        return false;
    }

    current_param++;

    if(params_finished(current_param, input_str)){
        //If nothing more

        if(index>arr->size || (index+count)>arr->size){
            //If outside the size
            free(values);
            error = index_out_of_bounds;
            #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
            print_error(help_msg);
            #endif
            return false;
        }

        //Actual realization of the command
        set_values_at(arr->ptr, index, values, count);
        free(values);
        return true;
    }
    else{
        //If more in the command
        free(values);
        error = too_many_parameters;
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        print_error(help_msg);
        #endif
        return false;
    }

    return true;
}

void set_values_at(int* arr, unsigned int index, int* values, unsigned int num_values){
    /*
        Changes the values contained in arr with values contained in values
        starting from index to (index+num_values-1)

        In this function, 'index' and (index + num_values-1) are assumed to be
        both inside the array size.
    */

    for(unsigned int i=index; i<(index+num_values); i++){
        arr[i] = values[i-index];
    }

    return;
}