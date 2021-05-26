#include <stdio.h> // NULL

#include "alias_utils.h"

void remove_alias(ALIAS* alias){
	/*
		Removes the given alias from the stack, if it is contained
	*/
	if(alias == NULL){
		return;
	}

	if(alias_list == alias){
		delete_alias( pop_alias() );
		return;
	}

	if(alias_list==NULL || alias_list->next_alias==NULL){
		return;
	}

	ALIAS* tmp = alias_list->next_alias;
	ALIAS* prev = alias_list;
	while(tmp != NULL){
		if(tmp==alias){
			break;
		}
		else{
			prev = tmp;
			tmp = tmp->next_alias;
		}
	}

	if(tmp == NULL){
		return;
	}

	prev->next_alias = tmp->next_alias;

	delete_alias(tmp);
}