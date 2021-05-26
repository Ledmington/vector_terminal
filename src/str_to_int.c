#include <string.h>
#include <ctype.h>

#include "utils.h"
#include "error.h"

int str_to_int(const char* str){
	/*
		This function is necessary because 'strtol' does not deal well with errors.

		Returns 0 if an error has occurred. (the variable 'error' is set properly)
		Returns the correct value otherwise.
	*/
    unsigned int length = strlen(str);
    int sign = 0;
    unsigned int index = 0;
    int old_value = 0;
    int new_value = 0;
    
    //Optional sign at the beginning
    if(str[index]=='+'){
        sign = 1;
        index++;
    }
    else if(str[index]=='-'){
        sign = -1;
        index++;
    }
    
    //If sign omitted, the number is positive
    if(sign==0) sign = 1;
    
    //Reading all the decimal digits
    while(index < length){
        if(isdigit(str[index])){
            new_value = new_value*10 + sign*(str[index]-'0');
            
            //Stronger overflow check
            if(sign==1 && (new_value/10)!=old_value){
                error = overflow_detected;
                return 0;
            }
            //Stronger underflow check
            else if(sign==-1 && (new_value/10)!=old_value){
                error = underflow_detected;
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