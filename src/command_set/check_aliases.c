#include <stdio.h>

#include "alias_utils.h"
#include "csv_utils.h"

char* check_aliases(char* str){
	//Searches valied aliases inside the given string and substitutes them if any is found

	for(unsigned int i=0; i<maxdep; i++){
		ALIAS* tmp = alias_list;
		while(tmp != NULL){

			str = substitute_alias(str, tmp);

			tmp = tmp->next_alias;
		}
	}

	return str;
}