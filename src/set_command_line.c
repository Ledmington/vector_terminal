#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "input_string_utils.h"
#include "command_set/csv_utils.h" // sep

INPUT_STRING* set_command_line(char* str) {
    /*
        Prepares the INPUT_STRING structure to be passed to the command function.
        At the end of this function, the pointer to the new structure is returned.

        The field 'num_parameters' will hold the number of sub-strings found.
        The field 'params' is an array to hold all the sub-strings already separated.
    */

	char quotes = '\"';

    unsigned int index = 0;
    unsigned int length = strlen(str);
    
    INPUT_STRING* result = (INPUT_STRING*) malloc(sizeof(INPUT_STRING));
    
    result->num_parameters = 0;
    result->params = NULL;
    
    while(index < length) {
        if(strchr(sep, str[index]) != NULL) index++;
        else if(str[index] == quotes) {
            //Tra virgolette
            result->params = (char**) realloc(result->params, (result->num_parameters+1)*sizeof(char*));
            result->num_parameters++;
            result->params[result->num_parameters-1] = (char*) calloc(maxin, sizeof(char));
            
            index++;
            unsigned int x = 0;

            while(index<length && str[index] != quotes) {
                result->params[result->num_parameters-1][x] = str[index];
                x++;
                index++;
            }
            index++;
        }
        else{
            //Senza virgolette
            result->params = (char**) realloc(result->params, (result->num_parameters+1)*sizeof(char*));
            result->num_parameters++;
            result->params[result->num_parameters-1] = (char*) calloc(maxin, sizeof(char));
            
            unsigned int x = 0;
            
            while(index<length && strchr(sep, str[index])==NULL) {
                result->params[result->num_parameters-1][x] = str[index];
                x++;
                index++;
            }
        }
        
    }

    //Eliminating the command name
    free(result->params[0]);
    for(unsigned int i=0; i<result->num_parameters-1; i++) {
    	result->params[i] = result->params[i+1];
    }
    result->params = (char**) realloc(result->params, (result->num_parameters-1)*sizeof(char*));
    result->num_parameters--;
    
    return result;
}