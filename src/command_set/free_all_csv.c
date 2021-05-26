#include <stdio.h>

#include "csv_utils.h"

void free_all_csv(){
	//Releases all the memory allocated for the CSV data structure
	CSV* tmp = csv_list;

	while(tmp != NULL){
		free_csv(tmp);
		tmp = tmp->next_csv;
	}
	csv_list = NULL;
}