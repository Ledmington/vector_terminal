#include <stdlib.h>
#include <stdio.h>

#include "../commands.h"
#include "history.h"
#include "../utils.h"

void update_history(const char* str){
    /*
        Creates a new 'HISTORY_STRING' structure at the top of the stack.
    */
    HISTORY_STRING* tmp = (HISTORY_STRING*) malloc(sizeof(HISTORY_STRING));
    tmp->command_string = new_string(str);
    tmp->next = NULL;

    if(first == NULL){
        first = tmp;
        last = tmp;
        return;
    }

    last->next = tmp;
    last = tmp;
}