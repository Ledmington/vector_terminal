#include <stdlib.h>

#include "command_set.h"

unsigned int* find_last(ARRAY* arr, comparing_function cmp_func, int value){
	/*
		Returns a pointer to an integer containing only the last occurrency of an element in the given array
		such that cmp_func(v[i], value) == true,
		if at least one of such elements exist.
		Returns NULL otherwise.
	*/

	for(unsigned int i=arr->size-1; i>=0; i--){
		if(cmp_func(arr->ptr[i], value) == true){
			unsigned int* result = (unsigned int*) malloc(2*sizeof(unsigned int));
			result[0] = 1;
			result[1] = i;
			return result;
		}
	}
	return NULL;
}