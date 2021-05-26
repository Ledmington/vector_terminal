#include <stdio.h>
#include <string.h>

#include "csv_utils.h"
#include "../error.h"

CSV* search_csv(char* name){
	/*
		Looks for the CSV with the given name in the CSVs data structure (or short_name)
		Returns a pointer to it, if such CSV structure exists;
		NULL otherwise.
		(the variable 'error' is set properly)
	*/
	if(name == NULL){
		error = csv_not_found;
		return NULL;
	}

	CSV* tmp = csv_list;

	while(tmp != NULL){
		if(!strcmp(name, tmp->name) || !strcmp(name, tmp->short_name)){
			error = no_error;
			return tmp;
		}

		tmp = tmp->next_csv;
	}

	error = csv_not_found;
	return NULL;
}