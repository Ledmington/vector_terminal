#pragma once

/*
    This structure is used just from the 'history' command to keep track of all
    commands sent.
    An illegal string, not corresponding to a command, is also saved in this structure.
    A command with wrong syntax is also saved in this structure.
    The resulting data structure is a linked list managed as a stack.
*/
typedef struct history_string{

    //The given input string
    char* command_string;

    //The pointer to the next structure
    struct history_string* next;

} HISTORY_STRING;