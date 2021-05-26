#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

/*
    This structure is the representation in memory of all arrays created during
    the execution.
    All these structures form a linked list managed as a stack.
*/
typedef struct array {

    //The name of the array
    char* name;

    //The number of elements contained in the array
    unsigned int size;

    /*
        The pointer to the array in memory, dinamically allocated.
        It is an array of integers, no other types available.
    */
    int* ptr;

    //Pointer to the next structure in the linked list
    struct array* next_array;

} ARRAY;

#endif // ARRAY_H_INCLUDED