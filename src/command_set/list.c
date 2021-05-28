#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command_set.h"
#include "../api.h"
#include "../error.h"
#include "../parameters.h"

extern unsigned int NUM_ARRAYS;

// Alphabetical sorting
int alph_sort(const void *a, const void *b) {
    ARRAY* v1 = *(ARRAY**) a;
    ARRAY* v2 = *(ARRAY**) b;
    return strcmp(v1->name, v2->name);
}

// "Numerical" sorting
int size_sort(const void *a, const void *b) {
    ARRAY* v1 = *(ARRAY**) a;
    ARRAY* v2 = *(ARRAY**) b;
    return (int)(v1->size) - (int)(v2->size);
}

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
    ARRAY* array_tmp;

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
        // Create temporary list
        ARRAY** tmp_list = (ARRAY**) malloc(NUM_ARRAYS * sizeof(ARRAY*));
        array_tmp = array_list;
        for(unsigned int i=0; i<NUM_ARRAYS; i++) {
            tmp_list[i] = array_tmp;
            array_tmp = array_tmp->next_array;
        }

        if(sort_by_name) {
            // Sort alphabetically
            qsort(tmp_list, NUM_ARRAYS, sizeof(ARRAY*), alph_sort);
        }
        else if(sort_by_size) {
            // Sort "numerically"
            qsort(tmp_list, NUM_ARRAYS, sizeof(ARRAY*), size_sort);
        }

        if(descending) {
            // Reverse temporary list
            for (unsigned int i = 0; i < NUM_ARRAYS/2; i++) {
                ARRAY* temp = tmp_list[i];
                tmp_list[i] = tmp_list[NUM_ARRAYS - 1 - i];
                tmp_list[NUM_ARRAYS - 1 - i] = temp;
            }
        }

        // Print temporary list
        for(unsigned int i=0; i<NUM_ARRAYS; i++) {
            sprintf(tmp, "Name: %s\n"
                         "Size: %u\n\n", tmp_list[i]->name, tmp_list[i]->size);
            appout(tmp);
        }

        free(tmp_list);
    }

    error = no_error;
    return true;
}