#include "utils.h"

void merge_sort(int* v, int* aux, unsigned int start, unsigned int end){
    if(start < end){

        unsigned int middle = (start + end)/2;

        merge_sort(v, aux, start, middle);
        merge_sort(v, aux, middle+1, end);

        merge(v, aux, start, middle, end);
    }
}