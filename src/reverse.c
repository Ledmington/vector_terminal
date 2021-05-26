#include "utils.h"

void reverse(int* v, unsigned int start, unsigned int end){
    for(unsigned int i = start; i<=(start+end)/2; i++){
        swap(&v[i], &v[end-i]);
    }
}