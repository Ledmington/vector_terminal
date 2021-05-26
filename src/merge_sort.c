#include "utils.h"

void merge_sort(int* v, unsigned int start, unsigned int end){
    if(start < end){

        unsigned int middle = (start + end)/2;

        merge_sort(v, start, middle);
        merge_sort(v, middle+1, end);

        merge(v, start, middle, end);
    }
}