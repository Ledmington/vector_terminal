#include <stdio.h> // NULL

#include "csv_utils.h"

CSV* pop_csv(){
	//Removes the first CSV structure in the CSV data structure and returns a pointer to it

	if(csv_list == NULL){
		return NULL;
	}

	CSV* tmp = csv_list;

	csv_list = csv_list->next_csv;

	tmp->next_csv = NULL;

	return tmp;
}