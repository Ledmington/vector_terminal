#ifndef ALIAS_H_INCLUDED
#define ALIAS_H_INCLUDED

/*
	The structure to hold the informations about an alias.
*/
typedef struct alias {

	//The string to be substituted
	char* str_to_sub;

	//The string replacing str_to_sub
	char* new_string;

	//Pointer to the next ALIAS structure in the ALIASes stack
	struct alias* next_alias;
} ALIAS;

#endif // ALIAS_H_INCLUDED