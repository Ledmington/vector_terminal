#include <stdio.h>
#include <stdlib.h>

#include "api.h"
#include "command_set/csv_utils.h"
#include "commands.h"
#include "command_set/history.h"
#include "command_set/alias_utils.h"

void VT_end() {
	/*
		Deletes all the memory allocated during the execution of this program
	*/
	clear_command_set();

	//Delete all history
    HISTORY_STRING* hs_tmp = history_first;
    while(hs_tmp != NULL) {
        history_first = history_first->next;
        free(hs_tmp);
        hs_tmp = history_first;
    }
    history_last = NULL;

    //Delete all arrays
    ARRAY* array_tmp = array_list;
    while(array_tmp != NULL) {
        array_list = array_list->next_array;

        free_array(array_tmp);

        array_tmp = array_list;
    }

    clear_alias_list();

    save_all_csv();
    free_all_csv();

    free(fout);
    free(fin);
	free(sep);
	free(illchar);

    free(illegal_char_positions);

    #if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
    printf("Thank you for having used Vector Terminal. <3\n");
    #endif
}