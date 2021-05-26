#include <stdlib.h>

#include "alias_utils.h"
#include "../utils.h"

void add_alias(char* str_to_sub, char* new_str){
	/*
		Creates the new ALIAS structure and passes it to push_alias()
	*/
	ALIAS* tmp = (ALIAS*) malloc(sizeof(ALIAS));

	tmp->str_to_sub = new_string(str_to_sub);
	tmp->new_string = new_string(new_str);

	push_alias(tmp);
}