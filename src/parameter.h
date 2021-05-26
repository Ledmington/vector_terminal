#ifndef PARAMETER_H_INCLUDED
#define PARAMETER_H_INCLUDED

//The structure that holds all the information about a parameter.
typedef struct parameter {

    //If a parameter is mandatory or not
    bool mandatory;

    //The short name begins with '-' and is at most 2 characters long
    char* short_name;
    //The long name begins with '--' and has no specific length limits
    char* long_name;

    //Each parameter needs 0, 1 or 2 numbers in order to be used properly
    unsigned short int numbers_required;

    //Short description of how the parameter changes the command behavior
    char* description;

    //Pointer to the next parameter structure in the list of a command structure
    struct parameter *next_param;

} PARAMETER;

#endif // PARAMETER_H_INCLUDED