#include <stdio.h>

#include "commands.h"

void clear_command_set() {
    /*
        Deletes all the command set structures in memory.
    */

    while(command_set != NULL) {
        delete_command( pop_command() );
    }
}