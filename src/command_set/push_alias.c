#include <stdio.h>
#include <string.h>

#include "alias_utils.h"

void push_alias(ALIAS* new_alias){
	/*
		Adds the given ALIAS structure in the ALIASes stack
	*/
	if(new_alias == NULL ||
		new_alias->str_to_sub == NULL){
		return;
	}

	// If list is empty
	if(alias_list == NULL) {
		new_alias->next_alias = NULL;
		alias_list = new_alias;
		return;
	}

	// If new_alias is "less" than alias_list
	if(strcmp(new_alias->str_to_sub, alias_list->str_to_sub) < 0) {
		new_alias->next_alias = alias_list;
		alias_list = new_alias;
		return;
	}

	// General case
	ALIAS* tmp_alias = alias_list;
	while(tmp_alias->next_alias != NULL &&
		strcmp(tmp_alias->next_alias->str_to_sub, new_alias->str_to_sub) < 0) {
		tmp_alias = tmp_alias->next_alias;
	}

	new_alias->next_alias = tmp_alias->next_alias;
	tmp_alias->next_alias = new_alias;
}