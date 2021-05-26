#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0

#include <stdlib.h>

#include "commands.h"
#include "api.h"

void print_illegal_characters(unsigned int num_errors, char* str) {
	//Prints the formatted output to highlight the illegal characters

	//Printing the command string
	appout(str);
	appout("\n");

    //Printing spaces under each character until the first illegal character position is reached
    for(int i=0; i<illegal_char_positions[0]; i++) {
    	appout(" ");
    }
    appout("^");

    //For each other illegal character,
    //print spaces under each character until the next illegal character position is reached
    for(int i=1; i<num_errors; i++) {
        for(int j=0; j<(illegal_char_positions[i]-illegal_char_positions[i-1])-1; j++) {
            appout(" ");
        }
        appout("^");
    }

    appout("\n\nThe marked characters are illegal.\n\n");
    free(illegal_char_positions);
    output();
}
#endif