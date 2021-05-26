#include <stdio.h>
#include <string.h>

#include "csv_utils.h"

void push_csv(CSV* new_csv){
	//Adds the given CSV structure in the CSV data structure

	if(new_csv == NULL ||
	    new_csv->name == NULL){
		return;
	}

	// If list is empty
	if(csv_list == NULL) {
		new_csv->next_csv = NULL;
		csv_list = new_csv;
		return;
	}

	// If new_csv is "less" than csv_list
	if(strcmp(new_csv->name, csv_list->name) < 0) {
		new_csv->next_csv = csv_list;
		csv_list = new_csv;
		return;
	}

	// General case
	CSV* tmp_csv = csv_list;
	while(tmp_csv->next_csv != NULL &&
		strcmp(tmp_csv->next_csv->name, new_csv->name) < 0) {
		tmp_csv = tmp_csv->next_csv;
	}

	new_csv->next_csv = tmp_csv->next_csv;
	tmp_csv->next_csv = new_csv;
}