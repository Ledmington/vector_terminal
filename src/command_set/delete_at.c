#include <stdlib.h>

#include "command_set.h"
#include "../utils.h"

void delete_at(ARRAY* arr, bool index_defined, unsigned int index, bool value_defined, int value){

	if(index_defined == false){
		if(value_defined == false){
			//Mode 1
			arr->ptr = (int*) realloc( arr->ptr, (arr->size-1) * sizeof(int) );
			arr->size--;
			return;
		}
		else{
			//Mode 2
			unsigned int position;
			for(unsigned int i=0; i<arr->size; i++){
				if(arr->ptr[i] == value){
					shift_l_to_r(arr->ptr, arr->size, i);
					arr->ptr = (int*) realloc( arr->ptr, (arr->size-1) * sizeof(int) );
					arr->size--;
					return;
				}
			}
			return;
		}
	}
	else{
		if(value_defined == false){
			//Mode 3
			shift_l_to_r(arr->ptr, arr->size, index);
			arr->ptr = (int*) realloc( arr->ptr, (arr->size-1) * sizeof(int) );
			arr->size--;
			return;
		}
		else{
			//Mode 4
			if(arr->ptr[index] == value){
				shift_l_to_r(arr->ptr, arr->size, index);
				arr->ptr = (int*) realloc( arr->ptr, (arr->size-1) * sizeof(int) );
				arr->size--;
				return;
			}
			else{
				return;
			}
		}
	}
}