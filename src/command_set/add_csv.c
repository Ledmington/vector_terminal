#include <stdlib.h>
#include <stdio.h>

#include "csv_utils.h"
#include "../api.h"
#include "../utils.h"
#include "../error.h"

CSV* add_csv(char* name, char* short_name, char* description, TYPE new_t, VALUE new_value, VALUE_INFO* v_info){
	/*
		Creates a new CSV structure with the given data.
		If some parameters are empty, returns NULL.
	*/

	CSV* tmp = (CSV*) malloc(sizeof(CSV));
	if(tmp == NULL){
		#if !defined(VT_TEST_MODE) && VT_TEST_MODE==0
		char str[maxin];
        sprintf(str, "ERROR: cannot store CSV \"%s\" in memory.\n", name);
        appout(str);
        #endif
		return NULL;
	}

	if(check_empty_string(name) ||
	   check_empty_string(short_name) ||
	   check_empty_string(description)) return NULL;

	tmp->name = new_string(name);
	tmp->short_name = new_string(short_name);
	tmp->description = new_string(description);

	tmp->type = new_t;

	tmp->value_info = v_info;

	switch(new_t){
		case BIT:
			tmp->actual_value.b = new_value.b;
			tmp->default_value.b = new_value.b;
			// to ensure that boolean CSVs don't have the VALUE_INFO struct
			free(v_info);
			tmp->value_info = NULL;
			break;
		case UINTEGER:
			if(v_info == NULL){
				error = value_info_needed;
				#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
				print_error(help_msg);
				#endif
				return NULL;
			}
			if(new_value.x < v_info->range.min || new_value.x > v_info->range.max){
				error = invalid_number;
				#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
				print_error(help_msg);
				#endif
				return NULL;
			}
			tmp->actual_value.x = new_value.x;
			tmp->default_value.x = new_value.x;
			break;
		case STRING:
			if(v_info == NULL){
				error = value_info_needed;
				#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
				print_error(help_msg);
				#endif
				return NULL;
			}
			if(check_empty_string(v_info->pattern) ||
			   !pattern_match(new_value.s, v_info->pattern)){
				error = invalid_string;
				#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
				print_error(help_msg);
				#endif
				return NULL;
			}
			tmp->actual_value.s = new_string(new_value.s);
			tmp->default_value.s = new_string(new_value.s);
			break;
	}
		
	push_csv(tmp);
	return tmp;
}