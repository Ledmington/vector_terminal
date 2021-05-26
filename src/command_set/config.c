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
	*/

	unsigned int current_param = 0;
	COMMAND* cmd = search_command("config");
	CSV* tmp = search_csv(input_str->params[current_param]);

	if (tmp == NULL) {
		#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
		print_error(help_msg);
		#endif
		return false;
	}

	current_param++;

	if (search_parameter(cmd, input_str->params[current_param]) == search_parameter(cmd, "-d")) {
		reset(tmp);
		update_all_csv();
		return true;
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
			tmp->actual_value.x = a;
			break;
		case STRING:
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