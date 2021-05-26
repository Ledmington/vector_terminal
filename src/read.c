#include <string.h>
#include <stdlib.h>

#include "commands.h"
#include "utils.h"
#include "command_set/csv_utils.h" // fin
#include "error.h"
#include "api.h"

bool read(INPUT_STRING* input_str) {
	/*
		Reads commands from a file and executes them.
	*/
	FILE* f;
	char* file_name;

	if(input_str->num_parameters == 0) {
		file_name = new_string(fin);
	}
	else{
		file_name = new_string(input_str->params[0]);
		strcat(file_name, ".txt");
	}

	f = fopen(file_name, "r");

	if(f == NULL) {
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
		print_error_code(file_not_found, help_msg);
        #endif
		free(file_name);
		return false;
	}

	char* tmp;
	unsigned int line = 1;

	while(!feof(f)) {
		tmp = (char*) calloc(maxin, sizeof(char));
		fgets(tmp, maxin, f);
		if(strlen(tmp) > 0) {
			//eliminating the '\n' automatically copied by 'fgets'
			tmp[strlen(tmp)-1] = '\0';
		}
		if(strlen(tmp)>0 && check_sep_string(tmp)==false) {
            #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
			printf("%s, line %u: \"%s\"\n", file_name, line, tmp);
            #endif
			line++;
			input(tmp);
		}
		free(tmp);
	}

	free(file_name);
	fclose(f);
	return true;
}