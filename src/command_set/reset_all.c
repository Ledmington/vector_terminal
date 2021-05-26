#include <stdio.h> // NULL

#include "csv_utils.h"

void reset_all(){
	//Calls 'reset' to each CSV structure
	CSV* tmp = csv_list;

	while(tmp != NULL){
		reset(tmp);
		tmp = tmp->next_csv;
	}
}