#include <stdlib.h>

#include "csv_utils.h"

void free_csv(CSV* tmp_csv){
	//Releases the memory allocated for the given CSV structure
	free(tmp_csv->name);
	free(tmp_csv->short_name);
	free(tmp_csv->description);

	if(tmp_csv->type == STRING){
		free(tmp_csv->actual_value.s);
		free(tmp_csv->default_value.s);
	}

	if(tmp_csv->type != BIT) {
		free(tmp_csv->value_info->pattern);
	}

	free(tmp_csv->value_info);

	free(tmp_csv);
}