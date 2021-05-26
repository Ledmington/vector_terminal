#include <stdio.h>

#include "alias_utils.h"

ALIAS* pop_alias(){
	/*
		Removes the first ALIAS structure in the ALIASes stack.

		Returns NULL if the ALIASes stack is empty.
		Returns a pointer to the removed ALIAS structure otherwise.
	*/
	if(alias_list == NULL){
		return NULL;
	}

	ALIAS* tmp = alias_list;
	alias_list = alias_list->next_alias;
	tmp->next_alias = NULL;

	return tmp;
}