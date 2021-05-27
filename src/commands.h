#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

#include <stdbool.h>

#include "command.h"
#include "array.h"
#include "input_string.h"
#include "out_buffer.h"


//String with all the illegal characters
extern const char* illegal_characters;

/*
    Utility array.
    It's used only when at least one illegal character is found in the input string.
    In that case, it's set in order to contain all the positions in the input string
    of the illegal characters found.
*/
extern unsigned int* illegal_char_positions;

/*
    String with all the characters considered as word separators.
    If more than one are found between two words, only the first character
    is left and the others are ignored and discarded.
*/
extern const char* separators;

//This variable holds the value false until the command 'quit' is called
extern bool want_to_quit;


//Utility variable that holds the number of commands that are stored in the command_set list
extern unsigned int NUM_COMMANDS;

//The head of commands' queue
extern COMMAND* command_set;

//The tail of commands' queue
extern COMMAND* command_set_end;

//Pointer to the linked list that holds the informations about created arrays
extern ARRAY* array_list;

extern out_buffer* output_tail;
extern out_buffer* output_string;


//********COMMANDs****************

//This function prepares the COMMAND structure and passes it to push_command
COMMAND* add_command(char* name, char* description, char* usage, unsigned int min_params, unsigned int max_params, void* command_pointer);

//Function that frees the memory dinamically allocated for the creation of the COMMAND structure
void delete_command(COMMAND* cmd);

//Function which adds a new command at the end of the command_set queue
void push_command(COMMAND* cmd);

//Function that removes the structure at the top of the queue
COMMAND* pop_command(void);

//*******END COMMANDs*************

//*********COMMAND SET***********

//Creates the command set
void create_command_set(void);

//Releases all the memory alloacted by the COMMAND structure
void clear_command_set(void);

#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
//Prints all the commands' descriptions and parameters' description
void print_command_set(bool with_parameters);

//Same behavior of the one above
void print_command(COMMAND* cmd, bool with_parameters);
#endif

//********END COMMAND SET************

//********SEARCH FUNCTIONS***********

//Looks for a command with the given name in the command_set list
COMMAND* search_command(char* name);

//Looks for the array with given name in the array list
ARRAY* search_array(char* name);

//********END SEARCH FUNCTIONS*********


/*
    Counts all the illegal characters in the given string
    and sets 'illegal_char_positions' properly.
*/
unsigned int count_illegal_characters(char* str);

//Releases the memory allocated in an ARRAY structure
void free_array(ARRAY* array_tmp);

//Function that checks if there are enough parameters to execute that command
bool enough_parameters(COMMAND* cmd, INPUT_STRING* input_str);

//Saves the new string in the history
void update_history(const char* str);

#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
//Prints the formatted output to highlight the illegal characters
void print_illegal_characters(unsigned int num_errors, char* str);
#endif

/*
	FAKE COMMANDS
	This commands need to be separated from others because
	they are just a feature of the terminal.
*/
bool for_exec(INPUT_STRING* input_str);
bool read(INPUT_STRING* input_str);

//Counts the characters that are different in the two given strings
unsigned int count_char_diff(char* str, char* buffer);

#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
//Searches in the COMMANDs queue all the similar commands, and prints them
void print_similar_commands(char* str);
#endif

#endif // COMMANDS_H_INCLUDED