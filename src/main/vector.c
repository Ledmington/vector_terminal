#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../api.h"
#include "../commands.h"
#include "../command_set/csv_utils.h"
#include "../utils.h"

int main ( void ) {

    VT_start();

    while(want_to_quit == false) {

        printf("%s", linestart);

        char* input_string = (char*) calloc(maxin, sizeof(char));
        fgets(input_string, maxin, stdin);
        if( is_separator(input_string[strlen(input_string)-1]) ) {
            input_string[strlen(input_string)-1] = '\0';
        }

        input( input_string );
    }

	VT_end();

	return 0;
}