#include "error.h"

error_code error = no_error;

const char* help_msg = "Type \'help\' or \'help COMMAND_NAME\' to know something more.";

#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
void print_error(const char* str) {
	print_error_code(error, str);
	error = no_error;
}
#endif