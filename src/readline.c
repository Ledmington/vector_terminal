#include <string.h>
#include <stdio.h>

#include "utils.h"

void readline(char* str, int n, FILE *f){
    fgets(str, n, f);
    if(str[strlen(str)-1] == '\n'){
        str[strlen(str)-1] = '\0';
    }
}