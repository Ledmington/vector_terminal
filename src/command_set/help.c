#include <stdio.h>

#include "command_set.h"
#include "../commands.h"
#include "../parameters.h"
#include "../error.h"
#include "../utils.h"

bool help(INPUT_STRING* input_str){
    /*
        Prints useful informations about specified command
    */
    bool with_parameters = true;
    COMMAND* cmd = search_command("help");
    PARAMETER* short_desc_param = search_parameter(cmd, "-s");
    char* pattern = NULL;

    for(int p=0; p<input_str->num_parameters; p++) {
        if(search_parameter(cmd, input_str->params[p]) == short_desc_param) {
            if(!with_parameters) {
                #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
                print_error("cannot set the flag \"-s\" twice");
                #endif
                return false;
            }
            with_parameters = false;
        }
        else {
            if(pattern != NULL) {
                #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
                print_error("cannot define a pattern twice");
                #endif
                return false;
            }
            pattern = input_str->params[p];
        }
    }

    if(pattern == NULL) {
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        print_command_set(with_parameters);
        #endif
    }
    else {
        COMMAND* tmp_cmd = command_set;
        #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
        while(tmp_cmd != NULL) {
            if(pattern_match(tmp_cmd->name, pattern)) {
                print_command(tmp_cmd, with_parameters);
            }
            tmp_cmd = tmp_cmd->next_cmd;
        }
        #endif
    }

    return true;
}