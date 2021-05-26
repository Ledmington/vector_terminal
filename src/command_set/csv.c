#include "csv_utils.h"
#include "../commands.h"
#include "../parameters.h"
#include "../error.h"

bool csv(INPUT_STRING* input_str){
	/*
		If called without '-a' prints just names and values,
		otherwise, prints also descriptions.
	*/
	COMMAND* cmd = search_command("csv");

	if(input_str->num_parameters == 0){
		#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
		print_all_csv(false);
		#endif
		return true;
	}

	if(search_parameter(cmd, input_str->params[0]) == search_parameter(cmd, "-a")){
		#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
		print_all_csv(true);
		#endif
		return true;
	}
	else{
		#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
		print_error(help_msg);
		#endif
		return false;
	}
}