#include <stdio.h>
#include <stdlib.h>

#include "api.h"
#include "commands.h"
#include "utils.h"

out_buffer* output_tail = NULL;
out_buffer* output_string = NULL;

void appout(const char* str) {
	// Appends the given string to 'output_string'
	out_buffer* tmp = (out_buffer*) malloc(sizeof(out_buffer));

	if(output_tail == NULL) {
		output_tail = tmp;
		output_string = tmp;
	}
	else{
		output_tail->next = tmp;
        output_tail = tmp;
	}
	tmp->next = NULL;
	tmp->message = new_string(str);
}