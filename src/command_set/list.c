#include <stdio.h>

#include "command_set.h"
#include "../api.h"
#include "../error.h"
#include "../parameters.h"

bool list(INPUT_STRING* input_str){
    /*
        Prints the list of all existing arrays    
    */
    char tmp[100];
    COMMAND* cmd = search_command("list");
    bool ascending = false;
    bool descending = false;
    bool sort_by_name = false;
    bool sort_by_size = false;



    for(unsigned int current_param = 0; current_param < input_str->num_parameters; current_param++) {
        if(search_parameter(cmd, input_str->params[current_param]) == search_parameter(cmd, "-a")) {
            ascending = true;
        }
        else if(search_parameter(cmd, input_str->params[current_param]) == search_parameter(cmd, "-d")) {
            descending = true;
        }
        else if(search_parameter(cmd, input_str->params[current_param]) == search_parameter(cmd, "-alp")) {
            sort_by_name = true;
        }
        else if(search_parameter(cmd, input_str->params[current_param]) == search_parameter(cmd, "-s")) {
            sort_by_size = true;
        }
        else {
            error = parameter_not_found;
            #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
            print_error(help_msg);
            #endif
            return false;
        }
    }


    if((ascending && descending) || (sort_by_name && sort_by_size)) {
        error = invalid_ordering;
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        print_error(help_msg);
        #endif
        return false;
    }

    if(!ascending && !descending && (sort_by_name ^ sort_by_size)) {
        ascending = true;
    }
    if(!sort_by_name && !sort_by_size) {
        sort_by_name = true;
    }

    if(array_list == NULL){
        appout("\n Array list is empty...\n\n");
    }
    else {
        if(sort_by_name) {
            // Sort alphabetically
        }
        else if(sort_by_size) {
            // Sort "numerically"
        }

        if(descending) {
            // Reverse temporary list
        }

        // Print temporary list
        ARRAY* array_tmp = array_list;
        while(array_tmp != NULL){
            sprintf(tmp, "Name: %s\n"
                         "Size: %u\n\n", array_tmp->name, array_tmp->size);
            appout(tmp);

            array_tmp = array_tmp->next_array;
        }
    }

    error = no_error;
    return true;
}