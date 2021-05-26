#include <string.h>
#include <ctype.h>

#include "utils.h"
#include "error.h"

unsigned int str_to_uint(const char* str){
	/*
		This function is necessary because 'strtol' does not deal well with errors.

		Returns 0 if an error has occurred. (the variable 'error' is set properly)
		Returns the correct value otherwise.
	*/
    unsigned int length = strlen(str);
    unsigned int index = 0;
    unsigned int old_value = 0;
    unsigned int new_value = 0;
    
    //Optional sign at the beginning
    if(str[index]=='+'){
        index++;
    }
    
    //Reading all the decimal digits
    while(index < length){
        if(isdigit(str[index])){
            new_value = new_value*10 + (str[index]-'0');
            
            //Stronger overflow check
            if((new_value/10)!=old_value){
                error = overflow_detected;
                return 0;
            }
        }
        else{
            error = conversion_failed;
            return 0;
        }
        
        old_value = new_value;
        index++;
    }
    
    error = no_error;
    return new_value;
}