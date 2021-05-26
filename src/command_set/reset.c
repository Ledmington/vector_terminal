#include <stdio.h> // NULL

#include "csv_utils.h"
#include "../utils.h"

void reset(CSV* tmp_csv){
	//Sets the actual value of the given CSV structure to the default value
	if(tmp_csv == NULL){
		return;
	}

	if(tmp_csv->type == STRING){
		tmp_csv->actual_value.s = new_string(tmp_csv->default_value.s);
		return;
	}

	tmp_csv->actual_value = tmp_csv->default_value;
}