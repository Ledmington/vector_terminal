#pragma once

#include <stdbool.h>

#include "alias.h"
#include "../input_string.h"

//Pointer to the head of the ALIASes stack
ALIAS* alias_list;

//Looks for the alias with the given string to be substituted
ALIAS* search_alias(char* str_to_sub);

//This function prepares the ALIAS structure and passes it to push_alias()
void add_alias(char* str_to_sub, char* new_str);

//Adds the given ALIAS structure to the ALIASes stack
void push_alias(ALIAS* new_alias);

//Frees the given ALIAS structure
void delete_alias(ALIAS* alias);

//Removes and returns the first ALIAS structure in the ALIASes stack
ALIAS* pop_alias(void);

//Removes the given alias from the stack, if it is contained
void remove_alias(ALIAS* alias);

#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
//Prints the content of an ALIAS structure
void print_alias(ALIAS* alias);

//Prints the contents of every ALIAS structure in the ALIASes stack
void print_alias_list(void);
#endif

//Deletes all ALIAS structures in ALIASes stack
void clear_alias_list(void);

//Fills the list with default aliases
void create_alias_list(void);

//Searches valied aliases inside the given string and substitutes them if any is found
char* check_aliases(char* str);

//Substitutes every occurrency inside the given string with the corresponding alias
char* substitute_alias(char* str, ALIAS* alias);

//Real commands
bool alias(INPUT_STRING* input_str);
bool unalias(INPUT_STRING* input_str);