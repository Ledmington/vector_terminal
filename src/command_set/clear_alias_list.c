#include <stdio.h>

#include "alias_utils.h"

void clear_alias_list(){
	/*
		Deletes all the ALIASes stack
	*/
	while(alias_list != NULL){
		delete_alias( pop_alias() );
	}
}