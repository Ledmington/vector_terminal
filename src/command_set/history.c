#include "csv_utils.h"
#include "history.h"
#include "../utils.h"
#include "../api.h"
#include "../error.h"

bool history(INPUT_STRING* input_str){

    char str[maxin];

    if(input_str->num_parameters == 0){
        HISTORY_STRING* tmp = first;
        unsigned int index = 1;
        while(tmp != NULL){
            #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
            sprintf(str, "\t%3u  ->  %s\n", index, tmp->command_string);
            appout(str);
            #endif
            index++;
            tmp = tmp->next;
        }
    }
    else if(input_str->num_parameters == 1){
        unsigned int command_num = str_to_uint(input_str->params[0]);
        if(command_num == 0 && error != no_error){
            #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
            print_error(help_msg);
            #endif
            return false;
        }
        else{
            HISTORY_STRING* tmp = first;
            unsigned int index = 1;
            while(tmp!=NULL && index<command_num){
                index++;
                tmp = tmp->next;
            }
            if(tmp == NULL){
            	error = command_not_found;
                #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
                print_error(help_msg);
                #endif
                return false;
            }
            if(index == command_num){
                /*
                    THIS RECURSION IS A BAD FEATURE
                */
                input(tmp->command_string);
                return true;
            }
        }
    }

    error = no_error;
    return true;    
}