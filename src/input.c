#include <string.h>
#include <stdlib.h>

#include "api.h"
#include "utils.h"
#include "command_set/csv_utils.h"
#include "commands.h" // update_history
#include "command_set/alias_utils.h" // check_aliases
#include "input_string_utils.h"
#include "error.h"

void input(char* str) {
    /*
        Reads the input string, checks the syntax and grammar,
        parses the given command and calls the appropriate command.
    */

    update_all_csv();

    if(strlen(str)==0 || check_sep_string(str)) {
        error = no_error;
        return;
    }
    

    unsigned int count_errors = count_illegal_characters(str);

    if(count_errors > 0) {

        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
    	print_illegal_characters(count_errors, str);
        #endif
    	
        error = invalid_string;
        return;
    }

    if(upall == false) {
    	str_to_lower(str);
    }


    if(histal==true) {
    	//Saving history only if the right CSV is set to true
	    if(hist==true) {
		    update_history(str);
		}

		/*
	    	Checking if the user is calling the command unalias
	    	THIS IS A BAD FEATURE
	    	IT'S LIKE PUTTING MAGIC NUMBERS
	    */
	    if(strstr(str, "unalias") != str) {
	    	//Substituting all the aliases found in the string
	    	str = check_aliases(str);
	    }
    }  
    else if(histal==false) {
    	/*
	    	Checking if the user is calling the command unalias
	    	THIS IS A BAD FEATURE
	    	IT'S LIKE PUTTING MAGIC NUMBERS
	    */
	    if(strstr(str, "unalias") != str) {
	    	//Substituting all the aliases found in the string
	    	str = check_aliases(str);
	    }

	    //Saving history only if the right CSV is set to true
	    if(hist==true) {
		    update_history(str);
		}
    }  

    

    unsigned int length = strlen(str);
    unsigned int current_position = 0;
    unsigned int start_position = 0;


    char* parsed_string = (char*) calloc(maxin, sizeof(char));
    for(; strchr(sep, str[start_position])!=NULL && str[start_position]!='\0'; start_position++) ;
    for(current_position=start_position; strchr(sep, str[current_position])==NULL && str[current_position]!='\0'; current_position++) ;

    strncpy(parsed_string, &str[start_position], (current_position-start_position) );

    COMMAND* cmd = search_command(parsed_string);
    if(cmd != NULL) {

        INPUT_STRING* input_for_command = set_command_line(str);

        //Checking the correct number of parameters
        if(enough_parameters(cmd, input_for_command) == false) {
        	free(input_for_command);
        	return;
        }
        
        /*
			When implementing a command function, the INPUT_STRING structure passed
			is guaranteed to:
			have enough parameters
			have a reference to an array if the command needs one as first mandatory parameter

            NOTE: each command returns a boolean value:
            true if it worked fine,
            false if there was an error
            This value is not used here because it was added just for testing
        */
        cmd->command_ptr(input_for_command);

    	free_input_string(input_for_command);

        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        //The newline at the end of every command output
        appout("\n");
        #endif

    }
    else{
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
    	print_error(help_msg);
    	print_similar_commands(parsed_string);
        #endif

        free(parsed_string);
        return;
    }

    free(str);
    free(parsed_string);

    #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
    output();
    #endif

    error = no_error;
    return;
}