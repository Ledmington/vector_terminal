#pragma once

#include <stdbool.h>

#include "csv.h"
#include "../input_string.h"

bool save;
bool cout;
bool upall;
bool hist;
bool histal;

unsigned int maxin;
unsigned int maxarr;
unsigned int maxdep;
unsigned int maxdiff;

char* csvfile;
char* fout;
char* fin;
char* sep;
char* illchar;
char* linestart;

CSV* csv_list;


// Creates the list of CSV structures
void create_csv_list(void);

// Creates a CSV structure with the given data and calls push_csv()
CSV* add_csv(char* name, char* short_name, char* description, TYPE new_t, VALUE new_value, VALUE_INFO* v_info);

// Inserts the given CSV structure in the CSVs list
void push_csv(CSV* new_csv);

// Removes the first CSV structure in the CSV list and returns its pointer
CSV* pop_csv(void);

// Releases the memory allocated for the given CSV structure
void free_csv(CSV* tmp_csv);

// Releases all the memory allocated for the CSV data structure
void free_all_csv(void);

// Sets the 'actual_value' of the given CSV structure to the 'default_value'
void reset(CSV* tmp_csv);

// Calls 'reset(void)' on each CSV structure in the CSV list
void reset_all(void);

#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
// Prints the content of the given CSV structure
void print_csv(CSV* tmp_csv, const bool with_description);

// Prints the content of all the CSV structures in memory
void print_all_csv(const bool description);
#endif

// Looks for the CSV with the given name and returns a pointer to it
CSV* search_csv(char* name);

// The command csv
bool csv(INPUT_STRING* input_str);

// The command config
bool config(INPUT_STRING* input_str);

// Function to be called at the very start of each call to 'input'
// Updates the values of every CSV
void update_all_csv(void);

// Read the values of all CSVs from the file defined in "csvfile"
void load_all_csv(void);

// Writes the values of all CSVs on file defined in "csvfile"
// only if "save" is true
void save_all_csv(void);