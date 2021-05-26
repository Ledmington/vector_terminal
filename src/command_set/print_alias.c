#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0

#include <stdio.h>

#include "alias_utils.h"
#include "csv_utils.h"
#include "../api.h"

void print_alias(ALIAS* alias){
	/*
		Prints the informations contained in the given ALIAS structure
	*/
	if(alias == NULL){
		return;
	}

	char tmp[3*maxin];
	sprintf(tmp, "\"%s\" = \"%s\"", alias->str_to_sub==NULL?"":alias->str_to_sub, alias->new_string==NULL?"":alias->new_string);
	appout(tmp);
}

#endif