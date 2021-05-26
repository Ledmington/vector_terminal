#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "csv_utils.h"
#include "../utils.h"
#include "../error.h"

void load_all_csv(){
	FILE *f = fopen(csvfile, "r");
	int buffer_length = 100;
	char* buffer;
	CSV* tmp;

	while(!feof(f)){
		// for each line on the file
		buffer = read_until(f, buffer_length, '~');
		// avoid reading the '\n' at the end of the line
		fgetc(f);

		if(check_space_string(buffer)) continue;
		
		//the part before the '=' is the name, the other one is the value
		char* csv_name = strtok(buffer, "=");
		char* value = strtok(NULL, "=");

		tmp = search_csv(csv_name);
		if(tmp == NULL){
			#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
			printf("INTERNAL ERROR\n");
			printf("CSV named \"%s\" not existing\n", csv_name);
			printf("Someone have touched the csv file.\n");
			#endif
			return;
		}

		/*
			The first character of the value is the type:
				b for boolean,
				u for unsigned int,
				s for string.
			Generally, the string 'value' is formatted like this
				<1-char-type>"<actual-value>"
		*/

		// quick check that the type is correct
		char type_check;
		switch(tmp->type){
			case BIT:
				type_check = 'b';
				break;
			case UINTEGER:
				type_check = 'u';
				break;
			case STRING:
				type_check = 's';
				break;
		}
		if(type_check != value[0]){
			#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
			printf("INTERNAL ERROR\n");
			printf("CSV named \"%s\" has a value of type \'%c\' while the file says it is \'%c\'.\n", csv_name, type_check, value[0]);
			printf("Someone have touched the csv file.\n");
			#endif
			return;
		}

		char* avalue = strtok(value+1, "~");

		//actual conversion of the value
		switch(tmp->type){
			case BIT:
				if(!strcmp(avalue, "1")){
					tmp->actual_value.b = true;
				}
				else if(!strcmp(avalue, "0")){
					tmp->actual_value.b = false;
				}
				else{
					#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
					printf("INTERNAL ERROR\n");
					printf("CSV named \"%s\" is boolean but has a value different from \"1\" and \"0\".\n", csv_name);
					printf("The actual value is \"%s\".\n", avalue);
					printf("Someone have touched the csv file.\n");
					#endif
					return;
				}
				break;
			case UINTEGER:
				tmp->actual_value.x = str_to_uint(avalue);
				if(tmp->actual_value.x==0 && error!=no_error){
					#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
					printf("INTERNAL ERROR\n");
					printf("CSV named \"%s\" is unsigned int but the conversion failed.\n", csv_name);
					printf("The actual value is \"%s\".\n", avalue);
					printf("Someone have touched the csv file.\n");
					#endif
					return;
				}
				break;
			case STRING:
				tmp->actual_value.s = new_string(avalue);
				break;
		}

		free(csv_name);
		free(value);
		avalue = NULL;
	}
	fclose(f);
}