#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command_set.h"
#include "../utils.h"
#include "../error.h"
#include "../commands.h"
#include "../parameters.h"

bool add(INPUT_STRING* input_str){
	/*
		Adds an array of elements to the existing array.

		Without a specified index, the new elements are added at the end of the array,
		having it resized incrementing by 'count' its size.

		If the specified index is inside the array, all the elements from that position
		to the end get shifted by on position and the new element is inserted at the
		given index.

		If the specified index is outside the array, the array gets resized,
		all new elements are set to zero and the new element is added.
	*/

	COMMAND* cmd = search_command("add");
	unsigned int current_param = 0;
	unsigned int count = 0;
	int* new_values = NULL;

    ARRAY* arr = search_array(input_str->params[current_param]);
    if (arr == NULL) {
    	error = array_not_found;
    	#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
    	print_error(help_msg);
    	#endif
    	return false;
    }
    current_param++;

	//Counting values and verifying that they are valid integers
	do{
	    int value = str_to_int(input_str->params[current_param + count]);
	    if(value == 0 && error != no_error){
	    	#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
	    	print_error(help_msg);
	    	#endif
	    	return false;
	    }
	    count++;
	}while(!params_finished(current_param+count, input_str) && 
		(strcmp(input_str->params[current_param + count],"-i") && strcmp(input_str->params[current_param + count],"--index")) );

	//Preparing the array of new values to be added
	new_values = (int*) malloc(count * sizeof(int));
	for(unsigned int i=0; i<count; i++){
		new_values[i] = str_to_int(input_str->params[current_param + i]);
	}

    current_param += count;

    //No specified index, adding at the end
    if(params_finished(current_param, input_str)){
    	arr->ptr = (int*) realloc(arr->ptr, (arr->size+count) * sizeof(int));
    	arr->size += count;
    	add_at(arr, arr->size-count, new_values, count);
    	return true;
    }

    if(search_parameter(cmd, input_str->params[current_param]) == NULL){
    	#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
    	print_error(help_msg);
    	#endif
    	free(new_values);
    	return false;
    }

    current_param++;

    //Specifying '-i' without a number
    if(params_finished(current_param, input_str)){
    	error = number_needed;
    	#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
    	print_error(help_msg);
    	#endif
    	free(new_values);
    	return false;
    }

    unsigned int index = str_to_uint(input_str->params[current_param]);

    if(index >= arr->size){
    	arr->ptr = (int*) realloc(arr->ptr, (index+count) * sizeof(int));
    	for(unsigned int i=arr->size; i<=(index+count); i++){
    		arr->ptr[i] = 0;
    	}
    	arr->size = index+count;
    }
    else{
    	arr->ptr = (int*) realloc(arr->ptr, (arr->size+count) * sizeof(int));
    	arr->size += count;
    }

    add_at(arr, index, new_values, count);

	return true;
}

void add_at(ARRAY* arr, unsigned int index, int* values, unsigned int num_values){
	/*
		Adds the specified array of values at the specified index of the specified existing array.

		Example 1:
		vector = 0 1 2 3 4 5
		add_at(..., 2, [7,7,7], 3)
		vector = 0 1 7 7 7 2 3 4 5

		Example 2:
		vector = 0 1 2 3 4 5
		add_at(..., 8, [7,7,7], 3)
		vector = 0 1 2 3 4 5 0 0 7 7 7
	*/
	
	//Shifto in avanti gli elementi vecchi
	for(unsigned int i=arr->size-1; i>(arr->size-1-num_values); i--){
		arr->ptr[i] = arr->ptr[i-num_values];
	}

	//Inserisco i nuovi elementi
	for(unsigned int i=index; i<(index+num_values); i++){
		arr->ptr[i] = values[i-index];
	}

	free(values);
	return;
}