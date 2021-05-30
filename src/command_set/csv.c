#include <stdio.h>

#include "csv_utils.h"
#include "../commands.h"
#include "../parameters.h"
#include "../error.h"
#include "../utils.h"

bool csv(INPUT_STRING* input_str){
	/*
		If called without '-a' prints just names and values,
		otherwise, prints also descriptions.
	*/
	COMMAND* cmd = search_command("csv");
	bool with_descriptions = false;
	char* pattern = NULL;

	for(unsigned int current_param = 0; current_param < input_str->num_parameters; current_param++) {
		if(search_parameter(cmd, input_str->params[current_param]) == search_parameter(cmd, "-a")) {
			if(with_descriptions) {
				#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
				print_error("cannot set the flag \"-a\" twice");
				#endif
				return false;
			}
			else with_descriptions = true;
		}
		else {
			if(pattern != NULL) {
				#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
				print_error("cannot set the pattern twice");
				#endif
				return false;
			}
			pattern = input_str->params[current_param];
		}
	}

	if(pattern == NULL) {
		#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
		print_all_csv(with_descriptions);
		#endif
	}
	else {
		CSV* tmp_csv = csv_list;
		#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
		while(tmp_csv != NULL) {
			if(pattern_match(tmp_csv->name, pattern)) {
				print_csv(tmp_csv, with_descriptions);
			}
			tmp_csv = tmp_csv->next_csv;
		}
		#endif
	}

	return true;
}