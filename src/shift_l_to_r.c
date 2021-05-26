#include "utils.h"

void shift_l_to_r(int* v, unsigned int size, unsigned int index){
	for(unsigned int i=index; i<size-1; i++){
		v[i] = v[i+1];
	}
}