#include <stdlib.h>

#include "csv_utils.h"
#include "../utils.h"

char* csvfile   = NULL;
char* fout      = NULL;
char* fin       = NULL;
char* sep       = NULL;
char* illchar   = NULL;
char* linestart = NULL;

CSV* csv_list = NULL;

void create_csv_list(){
	//Creates the CSV data structure
	VALUE tmp;
	VALUE_INFO* vi;

	tmp.b = true;
	add_csv("SAVE_CSV", "save", "If true, saves all CSV values on file before quitting.", BIT, tmp, NULL);

	tmp.s = new_string("csv.txt");
	vi = (VALUE_INFO*) malloc(sizeof(VALUE_INFO));
	vi->pattern = new_string("*.txt");
	add_csv("CSV_FILE", "csvfile", "The file where all CSV values are stored.", STRING, tmp, vi);

	tmp.b = true;
	add_csv("CONSOLE_OUT_ACTIVATED", "cout", "Sets console stdout as default output, if true.\nIf false, the output is printed on file.", BIT, tmp, NULL);

	tmp.s = new_string("output.txt");
	vi = (VALUE_INFO*) malloc(sizeof(VALUE_INFO));
	vi->pattern = new_string("*.txt");
	add_csv("DEFAULT_OUTPUT_FILE", "fout", "The file where to print the output, if console is not activated.", STRING, tmp, vi);

	tmp.s = new_string("input.txt");
	vi = (VALUE_INFO*) malloc(sizeof(VALUE_INFO));
	vi->pattern = new_string("*.txt");
	add_csv("DEFAULT_INPUT_FILE", "fin", "The file where to read commands as input.", STRING, tmp, vi);

	tmp.s = new_string(" \t\n");
	vi = (VALUE_INFO*) malloc(sizeof(VALUE_INFO));
	vi->pattern = new_string("*");
	add_csv("SEPARATORS", "sep", "All valid string separators, they are used to split the command line.", STRING, tmp, vi);

	tmp.s = new_string("£$%&|\\/()=!?^*[]{}@#+.,:;°§<>");
	vi = (VALUE_INFO*) malloc(sizeof(VALUE_INFO));
	vi->pattern = new_string("*");
	add_csv("ILLEGAL_CHARACTERS", "illchar", "All invalid characters, typing one of them generates error.", STRING, tmp, vi);

	tmp.b = false;
	add_csv("UPPERCASE_ALLOWED", "upall", "If true, uppercase letters are allowed for array names.", BIT, tmp, NULL);

	tmp.x = 100;
	vi = (VALUE_INFO*) malloc(sizeof(VALUE_INFO));
	vi->range.min = 10;
	vi->range.max = 200;
	add_csv("MAX_INPUT_LENGTH", "maxin", "The maximum length of the input string.", UINTEGER, tmp, vi);

	tmp.x = 1000000;
	vi = (VALUE_INFO*) malloc(sizeof(VALUE_INFO));
	vi->range.min = 10;
	vi->range.max = 1000000;
	add_csv("MAX_ARRAY_SIZE", "maxarr", "The maximum length of an array.", UINTEGER, tmp, vi);

	tmp.x = 1;
	vi = (VALUE_INFO*) malloc(sizeof(VALUE_INFO));
	vi->range.min = 1;
	vi->range.max = 10;
	add_csv("MAX_DEPTH_RECURSIVE_ALIAS", "maxdep", "How many times the system must look for aliases to substitute in the input string.", UINTEGER, tmp, vi);

	tmp.b = true;
	add_csv("SAVE_HISTORY", "hist", "If true, each typed string is saved in the command history.", BIT, tmp, NULL);

	tmp.x = 2;
	vi = (VALUE_INFO*) malloc(sizeof(VALUE_INFO));
	vi->range.min = 1;
	vi->range.max = 5;
	add_csv("MAX_DIFFERENT_CHARS", "maxdiff", "Number of maximum different characters between a wrong typed command and the correct name.", UINTEGER, tmp, vi);

	tmp.b = true;
	add_csv("HISTORY_BEFORE_ALIAS", "histal", "Specifies whether a typed string is to be saved in history before or after aliases substitution.", BIT, tmp, NULL);

	tmp.s = new_string(" >> ");
	vi = (VALUE_INFO*) malloc(sizeof(VALUE_INFO));
	vi->pattern = new_string("*");
	add_csv("LINE_START", "linestart", "The characters to print at the start of the command line.", STRING, tmp, vi);
}