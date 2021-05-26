#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0

#include <stdio.h> // NULL

#include "alias_utils.h"
#include "../api.h"

void print_alias_list(){
	/*
		Prints the informations of all ALIASes structures
	*/

	if(alias_list == NULL){
		appout("\n No aliases set...\n");
		output();
		return;
	}

	ALIAS* tmp = alias_list;
	while(tmp != NULL){
		print_alias(tmp);
		appout("\n");
		tmp = tmp->next_alias;
	}
	output();
}

#endif