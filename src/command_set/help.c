#include <stdio.h>

#include "command_set.h"
#include "../commands.h"
#include "../parameters.h"
#include "../error.h"

bool help(INPUT_STRING* input_str){
    /*
        Prints useful informations about specified command
    */
    if(input_str->num_parameters == 0){
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
    	print_command_set(true);
        #endif
    	return true;
    }
    else{
        bool with_parameters = true;
        COMMAND* cmd_help = search_command("help");
        COMMAND* cmd_to_print = NULL;
        PARAMETER* short_desc_param = search_parameter(cmd_help, "-s");

        if(short_desc_param == NULL) {
            error = really_bad_error;
            #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
            print_error("a parameter is missing from \"help\" command structure");
            #endif
            return false;
        }

        for(int p=0; p<input_str->num_parameters; p++) {
            if(search_parameter(cmd_help, input_str->params[p]) == short_desc_param) {
                with_parameters = false;
            }
            else {
                if(cmd_to_print != NULL) {
                    #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
                    print_error("cannot ask for help for two commands");
                    #endif
                    return false;
                }

                cmd_to_print = search_command(input_str->params[p]);
                if(cmd_to_print == NULL){
                    #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
                    print_error(help_msg);
                    #endif
                    return false;
                }
            }
        }

        // Final output
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        if(!with_parameters && input_str->num_parameters==1) {
            print_command_set(with_parameters);
        }
        else {
            print_command(cmd_to_print, with_parameters);
        }
        #endif

        return true;
    }
}