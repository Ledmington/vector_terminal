#include <stdio.h>

#include "csv_utils.h"

void save_all_csv(){
	if(save == true){
		FILE *f = fopen(csvfile, "w");
		CSV* tmp = csv_list;

		while(tmp != NULL){
			fprintf(f,"%s=",tmp->name);
			switch(tmp->type){
				case BIT:
					fprintf(f,"b%u~", tmp->actual_value.b==true?1:0);
					break;
				case UINTEGER:
					fprintf(f,"u%u~", tmp->actual_value.x);
					break;
				case STRING:
					fprintf(f,"s%s~", tmp->actual_value.s);
					break;
			}
			fprintf(f,"\n");
			tmp = tmp->next_csv;
		}

		fclose(f);
	}
}