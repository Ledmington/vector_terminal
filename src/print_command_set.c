#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0

#include <stdio.h>

#include "commands.h"
#include "api.h"

void print_command_set(bool with_parameters) {
    /*
        Prints all the command_set structure including :
        - command names and descriptions
        - parameter names and descriptions
    */

    COMMAND *tmp = command_set;

    if(tmp == NULL) {
        appout("The command set is empty...\n\n");
        return;
    }

    while(tmp != NULL) {
        print_command(tmp, with_parameters);
        appout("\n");
        tmp = tmp->next_cmd;
    }
}
#endif