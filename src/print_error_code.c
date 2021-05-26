#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0

#include <stdio.h>

#include "error.h"
#include "api.h"

void print_error_code(const error_code err, const char* str) {
	/*
		Prints the error message corresponding to the given error code
		without changing the value of 'error'.
	*/
	appout("Error: ");
	switch(err) {
		case no_error:
			appout("No error has occurred, this string was meant not to be printed.");
			break;
		case too_many_parameters:
			appout("too many parameters.");
			break;
		case too_few_parameters:
			appout("too few parameters.");
			break;
		case array_not_found:
			appout("array not found.");
			break;
		case array_already_existing:
			appout("array already existing.");
			break;
		case overflow_detected:
			appout("overflow detected.");
			break;
		case underflow_detected:
			appout("underflow detected.");
			break;
		case conversion_failed:
			appout("conversion failed.");
			break;
		case invalid_name:
			appout("invalid name.");
			break;
		case array_size_too_big:
			appout("array size too big.");
			break;
		case parameter_not_found:
			appout("parameter not found.");
			break;
		case number_needed:
			appout("number needed.");
			break;
		case command_not_found:
			appout("command not found.");
			break;
		case syntax_error:
			appout("syntax error.");
			break;
		case index_out_of_bounds:
			appout("array index out of bounds.");
			break;
		case alias_not_found:
			appout("alias not found.");
			break;
		case alias_already_defined:
			appout("alias already defined.");
			break;
		case csv_not_found:
			appout("Configurable System Variable not found.");
			break;
		case csv_type_undefined:
			appout("a CSV has unknown type.");
			break;
		case file_not_found:
			appout("file not found.");
			break;
        case invalid_number:
            appout("invalid number.");
            break;
        case invalid_string:
            appout("invalid string.");
            break;
        case value_info_needed:
            appout("value_info struct needed.");
            break;
        case out_of_memory:
        	appout("out of memory.");
        	break;
        case really_bad_error:
        	appout("a really bad error happened.");
        	break;
        default:
            appout("WHAT? there's an undefined error type?");
            break;
	}

	appout("\n");
	if(str != NULL) {
		appout(str);
	}
	appout("\n");

	output();

	return;
}
#endif