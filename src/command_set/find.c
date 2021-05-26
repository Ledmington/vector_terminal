#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command_set.h"
#include "../utils.h"
#include "../commands.h"
#include "../error.h"
#include "../parameters.h"
#include "../api.h"

bool find(INPUT_STRING* input_str){
/*
    Prints all the elements in the specified array that satisfy the given condition

    The correct syntax for this command is:
    find ARRAY_NAME MODE COMPARING_FUNCTION
    where:
    	ARRAY_NAME is the name of the existing array where to search elements
    	MODE is the available mode of displaying the occurrencies found (can be just first, last or all)
    	COMPARING_FUNCTION is the function used to decide if an element is valid or not (can be just equal, less or greater)

    	ONE COMPARING FUNCTION IS MANDATORY

    In order to let this command syntax be a bit more flexible,
    if MODE is omitted, --all is used by default.
*/
    
    COMMAND* cmd = search_command("find");

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

    function_mode mode = NULL;
    
    PARAMETER* param_tmp = search_parameter(cmd, input_str->params[current_param]);
    if(param_tmp == NULL){
    	#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        print_error(help_msg);
        #endif
        return false;
    }

    //Setting the mode
    if(!strcmp(param_tmp->short_name, "-eq") || !strcmp(param_tmp->short_name, "-lt") || !strcmp(param_tmp->short_name, "-gt")){
    	mode = &find_all;
    }
    else{
    	if(!strcmp(param_tmp->short_name, "-f")){
    		mode = &find_first;
    	}
    	else if(!strcmp(param_tmp->short_name, "-l")){
    		mode = &find_last;
    	}
    	else if(!strcmp(param_tmp->short_name, "-a")){
    		mode = &find_all;
    	}
    	current_param++;
    }



    comparing_function compare = NULL;

    param_tmp = search_parameter(cmd, input_str->params[current_param]);
    if(param_tmp == NULL){
    	#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
    	print_error(help_msg);
    	#endif
        return false;
    }

    //Setting the comparing function
    if(!strcmp(param_tmp->short_name, "-eq")){
		compare = &is_equal_to;
	}
	else if(!strcmp(param_tmp->short_name, "-lt")){
		compare = &is_less_than;
	}
	else if(!strcmp(param_tmp->short_name, "-gt")){
		compare = &is_greater_than;
	}
	else{
		error = syntax_error;
		#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
		print_error(help_msg);
		#endif
		return false;
	}

	current_param++;

    int value = str_to_int(input_str->params[current_param]);
    if(value == 0 && error != no_error){
    	#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
    	print_error(help_msg);
    	#endif
        return false;
    }

    unsigned int* result = mode(vector, compare, value);

    char tmp[300];

    if(result == NULL){
    	#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
    	sprintf(tmp, "No elements found in array \'%s\' that satisfy the given condition.\n\n", vector->name);
    	appout(tmp);
    	#endif
    	return true;
    }

    #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
    for(unsigned int i=0; i<result[0]; i++){
    	char tmp2[100] = {0};
    	sprintf(tmp2, "%s[%u] = %d\n", vector->name, result[i+1], vector->ptr[ result[i+1] ]);
    	appout(tmp2);
    }
    #endif

    error = no_error;
    return true;
}

bool is_equal_to(int a, int b){
	return a == b;
}

bool is_less_than(int a, int b){
	return a < b;
}

bool is_greater_than(int a, int b){
	return a > b;
}