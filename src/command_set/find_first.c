#include <stdlib.h>

#include "command_set.h"

unsigned int* find_first(ARRAY* arr, comparing_function cmp_func, int value){
	/*
		Returns a pointer to an integer containing only the first occurrency of an element in the given array
		such that cmp_func(v[i], value) == true,
		if at least one of such elements exist.
		Returns NULL otherwise.
	*/
	for(unsigned int i=0; i<arr->size; i++){
		if(cmp_func(arr->ptr[i], value) == true){
			unsigned int* result = (unsigned int*) malloc(2*sizeof(unsigned int));
			result[0] = 1;
			result[1] = i;
			return result;
		}
	}
	return NULL;
}