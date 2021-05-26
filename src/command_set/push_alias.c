#include <stdio.h>

#include "alias_utils.h"

void push_alias(ALIAS* new_alias){
	/*
		Adds the given ALIAS structure in the ALIASes stack
	*/
	if(new_alias == NULL){
		return;
	}

	new_alias->next_alias = alias_list;
	alias_list = new_alias;
}