#include <stdio.h>

#include "alias_utils.h"
#include "csv_utils.h"

void create_alias_list(){
	/*
		Fills the list with default aliases:
		each CSV's short name is a default alias,
		others to add...
	*/

	CSV* tmp = csv_list;

	while(tmp != NULL){
		add_alias(tmp->short_name, tmp->name);
		tmp = tmp->next_csv;
	}
}