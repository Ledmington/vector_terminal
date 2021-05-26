#ifndef INPUT_STRING_H_INCLUDED
#define INPUT_STRING_H_INCLUDED

/*
    The structure that holds all the parameters given from input
    to be fed into the command function.
*/
typedef struct input_string {

    //Number of parameters (strings separated by valid separators)
    unsigned int num_parameters;

    //The array of actual parameters in the form of strings
    char** params;

} INPUT_STRING;

#endif // INPUT_STRING_H_INCLUDED