#include <stdlib.h>

#include "command_set.h"

unsigned int* find_all(ARRAY* arr, comparing_function cmp_func, int value){
	/*
		Returns an array containing all the occurrencies of elements in the given array
		such that cmp_func(v[i], value) == true,
		if at least one of such elements exist.
		Returns NULL otherwise.
	*/

	unsigned int count = 0;

	for(unsigned int i=0; i<arr->size; i++){
		if(cmp_func(arr->ptr[i], value) == true){
			count++;
		}
	}

	if(count == 0){
		return NULL;
	}

	unsigned int* result = (unsigned int*) malloc( (count+1)*sizeof(unsigned int) );
	result[0] = count;
	unsigned int index = 1;

	for(unsigned int i=0; i<arr->size; i++){
		if(cmp_func(arr->ptr[i], value) == true){
			result[index] = i;
			index++;
		}
	}

	return result;
}