#include <stdio.h>

#include "csv_utils.h"

void push_csv(CSV* new_csv){
	//Adds the given CSV structure in the CSV data structure

	if(new_csv == NULL){
		return;
	}

	new_csv->next_csv = csv_list;
	csv_list = new_csv;
}