#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0

#include <stdio.h> // NULL
#include <string.h>

#include "csv_utils.h"

void print_csv(CSV* tmp_csv, const bool with_description){
	//prints the content of the given CSV structure
	if(tmp_csv == NULL){
		return;
	}

	printf(" %s = ",tmp_csv->name);
	switch(tmp_csv->type){
		case BIT:
			printf("%s", tmp_csv->actual_value.b?"true":"false");
			break;
		case UINTEGER:
			printf("%u", tmp_csv->actual_value.x);
			break;
		case STRING:
			printf("\"");
			for(unsigned int i=0; i<strlen(tmp_csv->actual_value.s); i++){
				if(tmp_csv->actual_value.s[i] == '\t'){
					printf("\\t");
				}
				else if(tmp_csv->actual_value.s[i] == '\n'){
					printf("\\n");
				}
				else{
					printf("%c", tmp_csv->actual_value.s[i]);
				}
			}
			printf("\"");
			break;
	}

	printf("\n");

	if(with_description){
		printf("(\"%s\")\n", tmp_csv->short_name);
		printf("%s\n------------\n\n", tmp_csv->description);
	}
}
#endif