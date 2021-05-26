#include <string.h>

#include "commands.h"

#define min(a,b) (a<b)?a:b
#define max(a,b) (a>b)?a:b

unsigned int count_char_diff ( char* str, char* buffer ) {
	/*
		Counts the different characters in the two given strings.

		for each i, if str[i]!=buffer[i], the counter gets incremented.
		also, if strlen(str) != strlen(buffer), the counter is initialized with
		the difference betweeen lengths.
	*/
	unsigned int longest  = max( strlen(str), strlen(buffer) );
	unsigned int shortest = min( strlen(str), strlen(buffer) );
	unsigned int count = longest - shortest;

	for(unsigned int i=0; i<shortest; i++) {
		if(str[i] != buffer[i]) {
			count++;
		}
	}

	return count;
}