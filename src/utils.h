#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>

// A personal implementation of merge-sort
void merge_sort(int* v, const unsigned int start, const unsigned int end);
void merge(int* v, const unsigned int start, const unsigned int middle, const unsigned int end);
void swap(int* a, int* b);

// Reverses the given array from start to end indexes included
void reverse(int* v, const unsigned int start, const unsigned int end);

// Shifts all elements by 1 position, starting from index included
void shift_l_to_r(int* v, const unsigned int size, const unsigned int index);

// Converts the given string into an integer
int str_to_int(const char* str);

// Converts the given string into an unsigned integer
unsigned int str_to_uint(const char* str);

// Substitutes all alphabetic characters in lowercase letters
void str_to_lower(char* str);

// Useful way to set a string to a given value
char* new_string(const char* new);

// Checks whether the given string is NULL or empty
bool check_empty_string(const char* str);

// Checks whether the given string is composed only by characters in CSV "separators"
bool check_sep_string(const char* str);

// Checks whether the given string is composed only by "space" characters
bool check_space_string(const char* str);

// Checks whether the given character is a separator or not
bool is_separator(const char c);

// Reads a line from the file and removes the '\n' at the end
void readline(char* str, const int n, FILE *f);

// Reads from the given file until maxlen characters have been read or the stop character is encountered.
// Returns the string read.
char* read_until(FILE* f, const int maxlen, const char stop);

// Checks whether the given string matches the given pattern
bool pattern_match(const char* string, const char* pattern);

#endif