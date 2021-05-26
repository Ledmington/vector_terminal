#include <stdlib.h>

#include "commands.h"

void free_array(ARRAY* array_tmp) {
	//Releases the memory allocated in an ARRAY structure
	free(array_tmp->name);
	free(array_tmp->ptr);
	free(array_tmp);
}