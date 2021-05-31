#include "../../lib/minunit/minunit.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../utils.h"

MU_TEST(convert_int){
	// Empty string must return 0
	mu_check(str_to_int("") == 0);

	// Converting positive number without sign
	mu_check(str_to_int("1234") == 1234);

	// Converting positive number with '+'
	mu_check(str_to_int("+1234") == 1234);
	
	// Converting negative number
	mu_check(str_to_int("-1234") == -1234);
	
	// Converting number with a letter inside must return 0
	mu_check(str_to_int("12a34") == 0);
}

MU_TEST(convert_uint){
	// Empty string must return 0
	mu_check(str_to_uint("") == 0);

	// Converting positive number without sign
	mu_check(str_to_uint("1234") == 1234);

	// Converting positive number with '+'
	mu_check(str_to_uint("+1234") == 1234);
	
	// Converting negative number
	mu_check(str_to_uint("-1234") == 0);
	
	// Converting number with a letter inside must return 0
	mu_check(str_to_uint("12a34") == 0);
}

MU_TEST(file_reading){
	char* fname = "tmp.txt";
	FILE *f = fopen(fname, "w");

	fprintf(f, "abcdefghi\njklmnopq\nrstuvwxyz");
	fclose(f);
	f = fopen(fname, "r");

	mu_check(strcmp(read_until(f,10,'c'), "ab") == 0);

	remove(fname);
}

MU_TEST(string_creation){
	mu_check(strlen(new_string(NULL)) == 0);
}

MU_TEST(pattern_matching){
	//Test empty input
	mu_check(pattern_match(NULL, "a") == false);
	mu_check(pattern_match("", "a") == false);
	mu_check(pattern_match("a", NULL) == false);
	mu_check(pattern_match("a", "") == false);

	//Test equality
	mu_check(pattern_match("a", "a"));

	//Test wildcard '?'
	char s[2];
	s[1] = '\0';
	for(char c='a'; c<='z'; c++) {
		s[0] = c;
		mu_check(pattern_match(s, "?"));
	}

	//Test wildcard '*'
	for(char c='a'; c<='z'; c++) {
		s[0] = c;
		mu_check(pattern_match(s, "*"));
	}

	//Test mixed with '?'
	mu_check(pattern_match("abc", "?a?") == false);
	mu_check(pattern_match("abc", "a??"));
	mu_check(pattern_match("abc", "???"));
	mu_check(pattern_match("zzz", "???"));

	//Test mixed with '*'
	mu_check(pattern_match("abc", "*"));
	mu_check(pattern_match("abc", "**"));
	mu_check(pattern_match("abc", "a*"));
	mu_check(pattern_match("abc", "ab*"));
	mu_check(pattern_match("abc", "abc*"));
	mu_check(pattern_match("abc", "*c"));
	mu_check(pattern_match("abc", "*bc"));
	mu_check(pattern_match("abc", "*abc"));
	mu_check(pattern_match("abc", "*a*b*c*"));
	mu_check(pattern_match("abc", "*abcc") == false);
	mu_check(pattern_match("aab", "*ab"));

	//Test full
	mu_check(pattern_match("abc", "?b*"));
	mu_check(pattern_match("abc", "a*?c"));
	mu_check(pattern_match("abc.txt", "*.?") == false);
	mu_check(pattern_match("abcabcabcabc", "a*c*ab?"));
	mu_check(pattern_match("abcabcabcabc", "a*c*ab") == false);
	mu_check(pattern_match("abcabcabc", "a??*ca*ab") == false);
	mu_check(pattern_match("a", "*?*"));
}

MU_TEST_SUITE(test_utils){
	MU_RUN_TEST(convert_int);
	MU_RUN_TEST(convert_uint);
	MU_RUN_TEST(file_reading);
	MU_RUN_TEST(string_creation);
	MU_RUN_TEST(pattern_matching);
}

int main(){
	srand(time(NULL));

	MU_RUN_SUITE(test_utils);
	MU_REPORT();

	return MU_EXIT_CODE;
}