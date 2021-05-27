#pragma once

#include <stdbool.h>

// A little union to hold the value of a system variable
typedef union {
    bool b;
    unsigned int x;
    char* s;
} VALUE;

// A little enumeration to define the different types of value that a system variable can hold
typedef enum {
    BIT,        // ...because "BOOL" and "BOOLEAN" were already defined in libraries used by minunit
    UINTEGER,
    STRING
} TYPE;

// Little structure to hold minimum and maximum allowed values
typedef struct {
    unsigned int min;
    unsigned int max;
} VALUE_RANGE;

// Additional info about the value
typedef union {
    VALUE_RANGE range;
    char* pattern;
} VALUE_INFO;

typedef struct csv {

	// The name of the system variable
    char* name;

    // The short_name which is also a default alias
    char* short_name;

    // The description of the system variable
    char* description;

    // The type of the system variable
    TYPE type;

    // The actual value
    VALUE actual_value;

    // The default value
    VALUE default_value;

    // Additional info about the value
    VALUE_INFO* value_info;

	// Pointer to the next CSV structure
    struct csv* next_csv;

} CSV;