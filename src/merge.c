#include <stdlib.h>

#include "utils.h"
#include "command_set/csv_utils.h"

#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
#include "api.h" // appout
#endif

void merge(int* v, unsigned int start, unsigned int middle, unsigned int end){

  int* tmp = (int*) malloc((end-start+1) * sizeof(int));
  if(tmp == NULL){
    #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
    char str[maxin];
    sprintf(str, "(merge) cannot allocate array of size %u (%u bytes).\n",end-start+1, (end-start+1)*sizeof(int));
    appout(str);
    #endif
    return;
  }

  unsigned int pos1 = start;
  unsigned int pos2 = middle+1;
  unsigned int index = 0;

  while(pos1<=middle && pos2<=end){
    if(v[pos1] <= v[pos2]){
      tmp[index] = v[pos1];
      pos1++;
    }
    else{
      tmp[index] = v[pos2];
      pos2++;
    }
    index++;
  }

  while(pos1<=middle){
    tmp[index] = v[pos1];
    index++;
    pos1++;
  }

  while(pos2<=end){
    tmp[index] = v[pos2];
    index++;
    pos2++;
  }

  for(index=start; index<=end; index++){
    v[index] = tmp[index-start];
  }

  free(tmp);

}