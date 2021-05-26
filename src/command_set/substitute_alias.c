#include <string.h>
#include <stdlib.h>

#include "alias_utils.h"
#include "../utils.h"
#include "../api.h"
#include "csv_utils.h"

char* substitute_alias(char* str, ALIAS* alias){
    //This function returns a new string
    //Setting a bigger size of result and then resize

    char* result;
    unsigned int lenstr = strlen(str);
    unsigned int len1 = strlen(alias->str_to_sub);
    unsigned int len2 = strlen(alias->new_string);

    if(alias == NULL){
    	result = new_string(str);
    	return result;
    }

    char* position = strstr(str, alias->str_to_sub);

    if(position == NULL){
    	result = new_string(str);
    	return result;
    }

    //If str_to_sub found at the beginning and
    //the next character is inside the string and
    //it is a separator or a '\0'
    if(position==str && lenstr>=*(position+len1+1) && (is_separator(*(position+len1+1)) || (*(position+len1+1))=='\0' ) ){
    	result = (char*) calloc(maxin, sizeof(char));
    	strncat(result, alias->new_string, len2);
    	strncat(result, str+len1, strlen(str+len1));
    	result = (char*) realloc(result, (strlen(result)+1)*sizeof(char));
    }
    //if str_to_sub found not at the beginning and
    //the next character is inside the string and
    //it is a valid separator or a '\0'
    else if(position!=str && lenstr>=*(position+len1+1) && (is_separator(*(position+len1+1)) || (*(position+len1+1))=='\0' ) ){
    	result = (char*) calloc(maxin, sizeof(char));

    	//Copying the first part
    	strncat(result, str, position-str);

    	//Copying the found substring
    	strncat(result, alias->new_string, len2);

    	//Copying the last part
    	strncat(result, position+len1, strlen(position+len1));
    	
    	result = (char*) realloc(result, (strlen(result)+1)*sizeof(char));
    }
    else{
        // Is this a memory leak?
        // We create a new string for each alias substition?
        // We don't deallocate str, it seems...
    	result = new_string(str);
    }

    return result;
}