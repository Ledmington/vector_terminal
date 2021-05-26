#include <stdlib.h> // malloc

#include "utils.h"

int* find_all_char(char* string, char toSearch){
    unsigned int count = 0;
    unsigned int i = 0;
    while(string[i] != '\0'){
        if(string[i] == toSearch) count++;
        i++;
    }
    int* v = (int*) malloc((count+1) * sizeof(int));
    count = 0;
    i = 0;
    while(string[i] != '\0'){
        if(string[i] == toSearch) v[count++] = i;
        i++;
    }
    v[count] = -1;
}