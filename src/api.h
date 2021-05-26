#ifndef API_H_INCLUDED
#define API_H_INCLUDED

//Needed to be called before everything in the program
void VT_start(void);

/*
    Checks if the given string is valid.
    In that case, the string with all parameters is passed to the
    function pointed in the command structure.
*/
void input(char* str);

//Prints the content of 'output_string' on the correct output
void output(void);

//Appends the given string to 'output_string'
void appout(const char* str);

//Function to delete all the memory allocated during the execution of the program
void VT_end(void);

#endif // API_H_INCLUDED