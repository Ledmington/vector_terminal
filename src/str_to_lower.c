#include <string.h>
#include <ctype.h>

#include "utils.h"

void str_to_lower(char* str){
	/*
		Substitutes each uppercase letter in the given string
		with the corresponding lowercase one.
	*/

    unsigned int len = strlen(str);
    
    for(unsigned int i=0; i<len; i++){
        if(isalpha(str[i]) && isupper(str[i])){
            str[i] = tolower(str[i]);
        }
    }
}