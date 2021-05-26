#include <stdio.h>
#include <stdlib.h>

#include "api.h"
#include "commands.h"
#include "command_set/csv_utils.h"

void output() {
	/*
		Prints the content of 'output_string' on the correct output:
		if 'cout' is set to true, prints on stdout,
		otherwise, writes on file specified in 'fout'.
	*/
	if(output_string == NULL) {
		return;
	}

	//Output on console
	if(cout == true) {

		//Empties the output queue
		out_buffer* tmp = output_string;
		while(tmp != NULL) {
            printf("%s", tmp->message);
			tmp = tmp->next;
			output_string = tmp;
		}
		output_tail = NULL;
		
        //Freeing the queue
        tmp = output_string;
        while(tmp != NULL) {
            free(tmp->message);
            tmp = tmp->next;
            free(output_string);
            output_string = tmp;
        }
        
		return;
	}

	//Output on file
	FILE* f = fopen(fout, "w");

	//Empties the output queue
	out_buffer* tmp = output_string;
	while(tmp != NULL) {
		fprintf(f, "%s", tmp->message);
		tmp = tmp->next;
		output_string = tmp;
	}
	output_tail = NULL;

    //Closes file
	fclose(f);
	
    //Freeing the queue
	tmp = output_string;
	while(tmp != NULL) {
		free(tmp->message);
		tmp = tmp->next;
		free(output_string);
		output_string = tmp;
	}
}