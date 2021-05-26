#include <stdlib.h>

#include "alias_utils.h"

void delete_alias(ALIAS* alias){
	/*
		Releases the memory allocated for the given alias structure.
	*/
	free(alias->str_to_sub);
	free(alias->new_string);
	free(alias);
}