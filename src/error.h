#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

#include "error_code.h"

// The global variable that holds the informations about the errors
extern error_code error;

// An helping message to print in case of errors
extern const char* help_msg;

#if !defined(VT_TEST_MODE) || VT_TEST_MODE==0
// Prints the message corresponding to the specified error type
void print_error_code(const error_code err, const char* str);

// Prints the message corresponding to the value of the variable "error"
void print_error(const char* str);
#endif

#endif // ERROR_H_INCLUDED