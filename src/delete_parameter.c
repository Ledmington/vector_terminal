#include <stdlib.h> // free
#include <stdio.h> // NULL

#include "parameters.h"

void delete_parameter(PARAMETER* param_tmp) {
	/*
		This is just the free of a COMMAND
	*/
    if(param_tmp == NULL) return;

    free(param_tmp->short_name);
    free(param_tmp->long_name);
    free(param_tmp->description);
    free(param_tmp);
}