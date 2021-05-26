#include <stdlib.h>

#include "command_set.h"
#include "../utils.h"
#include "../error.h"
#include "../parameters.h"

bool delete(INPUT_STRING* input_str){
	/*
		Deletes an element in the given array.

		Mode 1:
			value not specified, index not specified
			the last element of the given array is deleted and the array gets resized.
		
		Mode 2:
			value specified, index not specified
			the first occurrency of value in the array is deleted and the array gets resized.
			if the given value is not found, nothing happens.

		Mode 3:
			value not specified, index specified
			the value contained at the given index is deleted and the array gets resized.

		Mode 4:
			value specified, index specified
			if the element at the given index contains the given element, it is deleted
			and the array gets resized, otherwise nothing happens.
	*/

	COMMAND* cmd = search_command("delete");

	bool with_value = false;
	int value;
	bool with_index = false;
	unsigned int index;

	unsigned int current_param = 0;

    ARRAY* arr = search_array(input_str->params[current_param]);
    if (arr == NULL) {
    	error = array_not_found;
    	#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
    	print_error(help_msg);
    	#endif
    	return false;
    }
    current_param++;

    if(params_finished(current_param, input_str)){
    	//No value and no index
    	goto call;
    }

    if(search_parameter(cmd, input_str->params[current_param]) == search_parameter(cmd, "-i")){
    	current_param++;
    	if(params_finished(current_param, input_str)){
    		error = number_needed;
    		#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
    		print_error(help_msg);
    		#endif
    		return false;
    	}
    	else{
    		index = str_to_uint(input_str->params[current_param]);
    		if(index == 0 && error != no_error){
    			#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
    			print_error(help_msg);
    			#endif
    			return false;
    		}

    		if(index >= arr->size){
    			error = index_out_of_bounds;
    			#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
    			print_error(help_msg);
    			#endif
    			return false;
    		}

    		//No value and with index
    		with_index = true;
    		goto call;
    	}
    }
    else{
    	
    	value = str_to_int(input_str->params[current_param]);
    	if(value == 0 && error != no_error){
    		#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
			print_error(help_msg);
			#endif
			return false;
    	}

    	with_value = true;

    	current_param++;
    	if(params_finished(current_param, input_str)){
    		//with value and no index
    		goto call;
    	}
    	else{
    		
    		if(search_parameter(cmd, input_str->params[current_param]) == search_parameter(cmd, "-i")){
		    	current_param++;
		    	if(params_finished(current_param, input_str)){
		    		error = number_needed;
		    		#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
		    		print_error(help_msg);
		    		#endif
		    		return false;
		    	}
		    	else{
		    		index = str_to_uint(input_str->params[current_param]);
		    		if(index == 0 && error != no_error){
		    			#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
		    			print_error(help_msg);
		    			#endif
		    			return false;
		    		}

		    		if(index >= arr->size){
		    			error = index_out_of_bounds;
		    			#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
		    			print_error(help_msg);
		    			#endif
		    			return false;
		    		}

		    		//With value and with index
		    		with_index = true;
		    		goto call;
		    	}
		    }

    	}
    }

    call:
    delete_at(arr, with_index, index, with_value, value);

	return true;
}