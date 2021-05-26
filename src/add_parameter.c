#include "parameters.h"
#include "commands.h"

PARAMETER* add_parameter(const bool mandatory, const char* short_name, const char* long_name, const unsigned short int numbers_required, const char* description) {
	/*
		This function's use is just shorten the function calls in 'createCommandSet'
		It calls 'addParameterIn' passing each parameter plus the pointer to the end of the queue
	*/
	return add_parameter_in(command_set_end, mandatory, short_name, long_name, numbers_required, description);
}