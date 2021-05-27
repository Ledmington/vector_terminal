#include <stdlib.h>

#include "utils.h"
#include "command_set/csv_utils.h"

void merge(int* v, int* aux, unsigned int start, unsigned int middle, unsigned int end){

    unsigned int pos1 = start;
    unsigned int pos2 = middle+1;
    unsigned int index = 0;

    while(pos1<=middle && pos2<=end){
        if(v[pos1] <= v[pos2]){
            aux[index] = v[pos1];
            pos1++;
        }
        else{
            aux[index] = v[pos2];
            pos2++;
        }
        index++;
    }

    while(pos1<=middle){
        aux[index] = v[pos1];
        index++;
        pos1++;
    }

    while(pos2<=end){
        aux[index] = v[pos2];
        index++;
        pos2++;
    }

    for(index=start; index<=end; index++){
        v[index] = aux[index-start];
    }
}