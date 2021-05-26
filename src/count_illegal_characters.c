#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "command_set/csv_utils.h" // illchar

unsigned int* illegal_char_positions = NULL;

unsigned int count_illegal_characters(char* str) {
    /*
        Checks every character of the given string.

        Returns the number of illegal characters found int given string.

        If this is number is at least one, the array 'illegal_char_positions' is
        filled with all the positions of every illegal character in the given string.
        Otherwise, that array is set to NULL;
    */

    free(illegal_char_positions);
    unsigned int count = 0;

    for(int i=0; i<strlen(str); i++) {
        for(int j=0; j<strlen(illchar); j++) {
            if(str[i] == illchar[j]) {
                count++;
            }
        }
    }

    if(count == 0) {
        illegal_char_positions = NULL;
        return 0;
    }

    illegal_char_positions = (unsigned int*) malloc(count * sizeof(unsigned int));
    unsigned int index = 0;
    for(unsigned int i=0; i<strlen(str); i++) {
        for(unsigned int j=0; j<strlen(illchar); j++) {
            if(str[i] == illchar[j]) {
                illegal_char_positions[index] = i;
                index++;
            }
        }
    }

    return count;
}