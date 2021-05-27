#include <stdio.h>
#include <string.h>

#include "csv_utils.h"
#include "../commands.h"
#include "../error.h"
#include "../parameters.h"
#include "../utils.h"

bool config ( INPUT_STRING* input_str ) {
	/*
		This command has just two different behaviors:
		examples:
		config fin ciao.txt
			sets the value of "DEFAULT_INPUT_FILE" to "ciao.txt"

		config fin -d
			sets the value of "DEFAULT_INPUT_FILE" to its default value ("input.txt")

		config -d -a
			sets the default value for all CSVs
	*/

	unsigned int current_param = 0;
	COMMAND* cmd = search_command("config");
	CSV* tmp = search_csv(input_str->params[current_param]);
	current_param++;
	bool reset_default = search_parameter(cmd, input_str->params[current_param]) == search_parameter(cmd, "-d");
	bool reset_all = (search_parameter(cmd, input_str->params[0]) == search_parameter(cmd, "-d")) &&
	                 (search_parameter(cmd, input_str->params[1]) == search_parameter(cmd, "-a"));

	if(tmp != NULL && reset_default) {
		reset(tmp);
		update_all_csv();
		return true;
	}
	else if(reset_all) {
		CSV* tmp_csv = csv_list;
			while(tmp_csv != NULL) {
				reset(tmp_csv);
				tmp_csv = tmp_csv->next_csv;
			}
			update_all_csv();
			return true;
	}
	else if(tmp == NULL) {
		error = csv_not_found;
		#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
		print_error(help_msg);
		#endif
		return false;
	}

	unsigned int a;

	switch (tmp->type) {
		case BIT:
			if (!strcmp(input_str->params[current_param], "true")) {
				tmp->actual_value.b = true;
			}
			else if (!strcmp(input_str->params[current_param], "false")) {
				tmp->actual_value.b = false;
			}
			else {
				error = invalid_string;
				#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
				print_error(help_msg);
				#endif
				return false;
			}
			break;
		case UINTEGER:
			a = str_to_uint(input_str->params[current_param]);
			if (a==0 && error!=no_error) {
				#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
				print_error(help_msg);
				#endif
				return false;
			}
			if(tmp->value_info != NULL &&
				(a<tmp->value_info->range.min || a>tmp->value_info->range.max)) {
				error = invalid_number;
				#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
				print_error(help_msg);
				#endif
				return false;
			}
			tmp->actual_value.x = a;
			break;
		case STRING:
			if(tmp->value_info != NULL && !pattern_match(input_str->params[current_param], tmp->value_info->pattern)) {
				error = invalid_string;
				#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
				print_error(help_msg);
				#endif
				return false;
			}
			tmp->actual_value.s = new_string(input_str->params[current_param]);
			break;
		default:
			#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
			printf("WHAT?!? this csv has a different type of value from bool, uint and string?\n");
			print_error_code(csv_type_undefined, help_msg);
			#endif
			return false;
			break;
	}

	update_all_csv();
	return true;
}