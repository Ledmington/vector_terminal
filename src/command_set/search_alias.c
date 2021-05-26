#include <stdio.h>
#include <string.h>

#include "alias_utils.h"
#include "../error.h"

ALIAS* alias_list = NULL;

ALIAS* search_alias(char* str_to_sub){
	/*
		Looks for an ALIAS structure containing the given string.

		Returns a pointer to ALIAS structure if such structure exists.
		Returns NULL otherwise.
			(and sets 'error' properly)
	*/
	ALIAS* tmp = alias_list;

	while(tmp != NULL){
		if(!strcmp(tmp->str_to_sub, str_to_sub)){
			error = alias_already_defined;
			return tmp;
		}
		tmp = tmp->next_alias;
	}

	error = alias_not_found;
	return NULL;
}