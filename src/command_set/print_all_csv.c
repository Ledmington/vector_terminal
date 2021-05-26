#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0

#include <stdio.h>

#include "csv_utils.h"

void print_all_csv(const bool description){
	//Prints the contents of all CSV structures
	CSV* tmp = csv_list;

	while(tmp != NULL){
		print_csv(tmp, description);
		tmp = tmp->next_csv;
	}
}
#endif