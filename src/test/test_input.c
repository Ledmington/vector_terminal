#include "../../lib/minunit/minunit.h"

#include "../api.h"
#include "../error.h"
#include "../command_set/csv_utils.h"

MU_TEST(input_empty){
	mu_check(error == no_error);
	input("");
	mu_check(error == no_error);
}

MU_TEST(input_separators){
	// Trying the whole separators string first
	mu_check(error == no_error);
	input(sep);
	mu_check(error == no_error);

	// Then trying with a string with each one of them
	char str[2] = "a";
	str[1] = '\0';
	for(int i=0; i<strlen(sep); i++){
		str[0] = sep[i];
		input(str);
		mu_check(error == no_error);
	}
}

MU_TEST(test_illegal){
	// Trying the whole illegal characters string first
	mu_check(error == no_error);
	input(illchar);
	mu_check(error == invalid_string);

	// Then trying with a string with each one of them
	char str[2] = "a";
	str[1] = '\0';
	for(int i=0; i<strlen(illchar); i++){
		str[0] = illchar[i];
		input(str);
		mu_check(error == invalid_string);
	}
}

MU_TEST_SUITE(test_input){
	MU_RUN_TEST(input_empty);
	MU_RUN_TEST(input_separators);
	MU_RUN_TEST(test_illegal);
}

int main(){

	VT_start();

	MU_RUN_SUITE(test_input);
	MU_REPORT();

	VT_end();

	return MU_EXIT_CODE;
}