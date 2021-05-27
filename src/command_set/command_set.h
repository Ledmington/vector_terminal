#ifndef COMMAND_SET_H_INCLUDED
#define COMMAND_SET_H_INCLUDED

#include "../commands.h"
#include "alias.h"
#include "csv.h"
#include "history.h"

/*
	Input structure for dynamic parameter functions
*/
typedef struct input {

	//Reference to the array
	ARRAY* ref;

	//Optional values
	int x[2];

} ARG;


bool params_finished(const unsigned int index, INPUT_STRING* input_str);

bool help(INPUT_STRING* input_str);

bool quit(INPUT_STRING* input_str);

bool list(INPUT_STRING* input_str);

bool create(INPUT_STRING* input_str);
void set(ARG* arg);
void set_from(ARG* arg);

bool add(INPUT_STRING* input_str);
void add_at(ARRAY* arr, const unsigned int index, int* values, const unsigned int num_values);

bool set_values(INPUT_STRING* input_str);
void set_values_at(int* arr, const unsigned int index, int* values, const unsigned int num_values);

bool delete(INPUT_STRING* input_str);
void delete_at(ARRAY* arr, const bool index_defined, const unsigned int index, const bool value_defined, const int value);

bool destroy(INPUT_STRING* input_str);

bool copy(INPUT_STRING* input_str);

bool append(INPUT_STRING* input_str);

bool sort(INPUT_STRING* input_str);
void sort_ascending(ARRAY* arr);
void sort_descending(ARRAY* arr);

bool print(INPUT_STRING* input_str);
void print_range(ARG* arr, const bool index);

//These two are used just in command find
typedef bool (*comparing_function)(const int a, const int b);
typedef unsigned int* (*function_mode)(ARRAY* arr, comparing_function cmp_func, const int value);

bool find(INPUT_STRING* input_str);
unsigned int* find_first(ARRAY* arr, comparing_function cmp_func, const int value);
unsigned int* find_all(ARRAY* arr, comparing_function cmp_func, const int value);
unsigned int* find_last(ARRAY* arr, comparing_function cmp_func, const int value);
static bool is_equal_to(const int a, const int b);
static bool is_less_than(const int a, const int b);
static bool is_greater_than(const int a, const int b);

bool version (INPUT_STRING* input_str);

#endif // COMMAND_SET_H_INCLUDED
