#include <stdlib.h>

#include "utils.h"

char* read_until(FILE* f, int maxlen, char stop) {
    /*
        Reads characters from the given file until either:
         - the end of file is encountered,
         - maxlen characters have been read,
         - the stop character is encountered.
         ... whatever occurs first.
        Returns the string read.
        The stop characters found are not copied, as well as the EOF character.
    */
    char* str = (char*) calloc(maxlen+1, sizeof(char));
    int i = 0;
    while (!feof(f) && i<=maxlen) {
        char ch = fgetc(f);
        if(ch == stop || ch == EOF) break;
        str[i] = ch;
        i++;
    }
    
    if (i < maxlen) {
        char* s = new_string(str);
        free(str);
        return s;
    }
    return str;
}